use std::error::Error;
use std::ops::DerefMut;
use std::thread;
use std::time::Duration;
use std::sync::{Arc, Mutex};
use std::sync::mpsc;
use std::sync::mpsc::Receiver;

use rppal::uart::{Parity, Uart};
use rppal::gpio::Gpio;
use rppal::i2c::I2c;

use linux_embedded_hal::Delay;

use clokwerk::{Scheduler, TimeUnits};

use chrono::prelude::*;

use nb::block;

use embedded_graphics::prelude::*;
use embedded_graphics::fonts::{Font6x8, Font8x16, Font24x32, Text};
use embedded_graphics::pixelcolor::BinaryColor;
use embedded_graphics::style::TextStyle;

use sh1106::prelude::*;
use sh1106::Builder;
use sh1106::displayrotation::DisplayRotation::Rotate90;

use bme280::BME280;

use embedded_ccs811::{Ccs811, SlaveAddr, MeasurementMode};
use embedded_ccs811::prelude::*;

const TICK_MS: u32 = 10;

#[derive(Default)]
struct DMCState {
    ambient_temperature: f32,
    ambient_humidity: f32,
    pressure: f32,
    e_co2: u16,
    e_tvoc: u16,
}

fn create_clock_job(job_notifier: Receiver<()>, uart_handle: Arc<Mutex<Uart>>) -> Box<dyn FnMut() + Send> {
    Box::new(move || {
        loop {
            job_notifier.recv().unwrap();
            {
                let mut uart = uart_handle.lock().unwrap();
                let localtime = Local::now();
                uart.write(format!("T{}\r\n", localtime.format("%H%M")).as_bytes()).unwrap();
            }
        }
    })
}

fn create_blink_colon_job(job_notifier: Receiver<()>, uart_handle: Arc<Mutex<Uart>>) -> Box<dyn FnMut() + Send> {
    Box::new(move || {
        loop {
            job_notifier.recv().unwrap();
            {
                let mut uart = uart_handle.lock().unwrap();
                uart.write("A\r\n".as_bytes()).unwrap();
                thread::sleep(Duration::from_millis(500));
                uart.write("D\r\n".as_bytes()).unwrap();
            }
        }
    })
}

fn create_display_job<'a, I2C, E>(
    job_notifier: Receiver<()>,
    display_handle: Arc<Mutex<GraphicsMode<I2cInterface<I2C>>>>,
    state_handle: Arc<Mutex<DMCState>>
) -> Box<dyn FnMut() + Send + 'a>
where I2C: 'a
           + embedded_hal::blocking::i2c::Write<Error = E> + Send,
      E: std::fmt::Debug,
{
    Box::new(move || {
        loop {
            job_notifier.recv().unwrap();
            {
                let localtime = Local::now();
                let state = state_handle.lock().unwrap();
                let mut display = display_handle.lock().unwrap();
                display.clear();
                Text::new(localtime.format("%S").to_string().as_str(), Point::new(0, 100))
                    .into_styled(TextStyle::new(Font24x32, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(localtime.format("%b %d").to_string().as_str(), Point::new(0, 67))
                    .into_styled(TextStyle::new(Font8x16, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(localtime.format("%a %Y").to_string().as_str(), Point::new(0, 81))
                    .into_styled(TextStyle::new(Font8x16, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(format!("{:.1} C", state.ambient_temperature).as_str(), Point::zero())
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(format!("{:.1} %", state.ambient_humidity).as_str(), Point::new(0, 8))
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(format!("{:.1} hPa", state.pressure / 100.0).as_str(), Point::new(0, 16))
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(format!("{} eCO2", state.e_co2).as_str(), Point::new(0, 32))
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                Text::new(format!("{} eTVOC", state.e_tvoc).as_str(), Point::new(0, 40))
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(display.deref_mut())
                    .unwrap();
                display.flush().unwrap();
            }
        }
    })
}

fn create_sensor_job<'a, I2C, D, E1, CCS811APP, E2>(
    job_notifier: Receiver<()>,
    bme280_handle: Arc<Mutex<BME280<I2C, D>>>,
    ccs811_handle: Arc<Mutex<CCS811APP>>,
    state_handle: Arc<Mutex<DMCState>>
) -> Box<dyn FnMut() + Send + 'a>
where I2C: 'a
           + embedded_hal::blocking::i2c::Write<Error = E1>
           + embedded_hal::blocking::i2c::Read<Error = E1>
           + embedded_hal::blocking::i2c::WriteRead<Error = E1>
           + Send,
      D: 'a
          + embedded_hal::blocking::delay::DelayMs<u8> + Send,
      CCS811APP: 'a
                 + embedded_ccs811::Ccs811AppMode<Error = E2> + Send,
      E1: std::fmt::Debug,
      E2: std::fmt::Debug,
{
    Box::new(move || {
        loop {
            job_notifier.recv().unwrap();
            let bme280_res = {
                let mut bme280 = bme280_handle.lock().unwrap();
                bme280.measure()
            }.unwrap();
            {
                let mut state = state_handle.lock().unwrap();
                state.ambient_temperature = bme280_res.temperature;
                state.ambient_humidity = bme280_res.humidity;
                state.pressure = bme280_res.pressure;
            }

            let ccs811_res = {
                let mut ccs811 = ccs811_handle.lock().unwrap();
                ccs811.set_environment(bme280_res.humidity, bme280_res.temperature)
                    .or_else::<(), _>(|e| {
                        println!("set_environment failed: {:?}", e);
                        Ok(())
                    }).unwrap();
                block!(ccs811.data())
            };
            match ccs811_res {
                Ok(res) => {
                    let mut state = state_handle.lock().unwrap();
                    state.e_co2 = res.eco2;
                    state.e_tvoc = res.etvoc;
                },
                Err(e) => {
                    println!("data() failed: {:?}", e);
                },
            }
        }
    })
}

fn main() -> Result<(), Box<dyn Error>> {
    // Initialize hardware access
    // UART
    let uart = Uart::with_path("/dev/ttyS0", 115200, Parity::None, 8, 1)?;
    let uart_handle = Arc::new(Mutex::new(uart));

    // I2C and software I2C(i2c-gpio)
    let i2c = I2c::new()?;
    let i2c: &'static _ = shared_bus::new_std!(I2c = i2c).unwrap();
    let software_i2c = linux_embedded_hal::I2cdev::new("/dev/i2c-2")?;

    // GPIO
    let gpio = Gpio::new()?;

    // SH1106 OLED display
    let mut display: GraphicsMode<_> = Builder::new().with_rotation(Rotate90).connect_i2c(i2c.acquire_i2c()).into();
    display.init().unwrap();
    display.flush().unwrap();
    let display_handle = Arc::new(Mutex::new(display));

    // BME280
    let mut bme280 = BME280::new_primary(i2c.acquire_i2c(), Delay);
    bme280.init().unwrap();
    let bme280_handle = Arc::new(Mutex::new(bme280));

    // CCS811
    let ccs811_nwake = gpio.get(4)?.into_output();
    let ccs811 = Ccs811::new(software_i2c, SlaveAddr::Alternative(true), ccs811_nwake, Delay);
    let mut ccs811 = ccs811.start_application().ok().unwrap();
    thread::sleep(Duration::from_millis(10));
    ccs811.set_mode(MeasurementMode::LowPowerPulseHeating60s).unwrap();
    let ccs811_handle = Arc::new(Mutex::new(ccs811));


    // Initialize other states
    let state = DMCState::default();
    let state_handle = Arc::new(Mutex::new(state));

    // Initialize scheduler
    let mut scheduler = Scheduler::new();

    // Create notifiers
    let (clock_job_notifier_tx, clock_job_notifier_rx) = mpsc::channel();
    let (colon_blink_job_notifier_tx, colon_blink_job_notifier_rx) = mpsc::channel();
    let (display_job_notifier_tx, display_job_notifier_rx) = mpsc::channel();
    let (sensor_job_notifier_tx, sensor_job_notifier_rx) = mpsc::channel();

    // Create jobs
    thread::spawn(create_clock_job(clock_job_notifier_rx, uart_handle.clone()));
    thread::spawn(create_blink_colon_job(colon_blink_job_notifier_rx, uart_handle.clone()));
    thread::spawn(create_display_job(display_job_notifier_rx, display_handle.clone(), state_handle.clone()));
    thread::spawn(create_sensor_job(
        sensor_job_notifier_rx,
        bme280_handle.clone(),
        ccs811_handle.clone(),
        state_handle.clone()
    ));

    // Schedule jobs
    scheduler.every(1.minute()).run(move || sensor_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.minute()).run(move || clock_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.second()).run(move || display_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.second()).run(move || colon_blink_job_notifier_tx.send(()).unwrap());

    // Do the main loop
    loop {
        scheduler.run_pending();
        thread::sleep(Duration::from_millis(TICK_MS as u64));
    }
}
