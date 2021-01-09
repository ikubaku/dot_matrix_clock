use std::error::Error;
use std::thread;
use std::time::Duration;
use std::sync::{Arc, Mutex};
use std::sync::mpsc;

use rppal::uart::{Parity, Uart};
use rppal::i2c::I2c;

use linux_embedded_hal::Delay;

use clokwerk::{Scheduler, TimeUnits};
use clokwerk::Interval::*;

use chrono::prelude::*;

use shared_bus::BusManagerStd;

use embedded_graphics::prelude::*;
use embedded_graphics::fonts::{Font6x8, Font24x32, Text};
use embedded_graphics::pixelcolor::BinaryColor;
use embedded_graphics::style::TextStyle;

use sh1106::prelude::*;
use sh1106::Builder;
use sh1106::displayrotation::DisplayRotation::Rotate90;

use bme280::BME280;

const TICK_MS: u32 = 10;

#[derive(Default)]
struct DMCState {
    ambient_temperature: f32,
}

fn main() -> Result<(), Box<dyn Error>> {
    // Initialize hardware access
    let uart = Uart::new(115200, Parity::None, 8, 1)?;
    let uart = Arc::new(Mutex::new(uart));
    let i2c = I2c::new()?;
    let i2c: &'static _ = shared_bus::new_std!(I2c = i2c).unwrap();
    let mut display: GraphicsMode<_> = Builder::new().with_rotation(Rotate90).connect_i2c(i2c.acquire_i2c()).into();
    display.init().unwrap();
    display.flush().unwrap();
    let mut bme280 = BME280::new_primary(i2c.acquire_i2c(), Delay);
    bme280.init().unwrap();

    // Initialize other states
    let state = DMCState::default();
    let state = Arc::new(Mutex::new(state));

    // Initialize scheduler
    let mut scheduler = Scheduler::new();

    // Create notifiers
    let (clock_job_notifier_tx, clock_job_notifier_rx) = mpsc::channel();
    let (colon_blink_job_notifier_tx, colon_blink_job_notifier_rx) = mpsc::channel();
    let (display_job_notifier_tx, display_job_notifier_rx) = mpsc::channel();
    let (sensor_job_notifier_tx, sensor_job_notifier_rx) = mpsc::channel();

    // Create jobs
    // clock
    let uart_proxy_clock = uart.clone();
    thread::spawn(move || {
        loop {
            clock_job_notifier_rx.recv().unwrap();
            {
                let mut uart_handle = uart_proxy_clock.lock().unwrap();
                let localtime = Local::now();
                uart_handle.write(format!("T{}\r\n", localtime.format("%H%M")).as_bytes()).unwrap();
            }
        }
    });

    // blink colon
    let uart_proxy_blink_colon = uart.clone();
    thread::spawn(move || {
        loop {
            colon_blink_job_notifier_rx.recv().unwrap();
            {
                let mut uart_handle = uart_proxy_blink_colon.lock().unwrap();
                uart_handle.write("A\r\n".as_bytes()).unwrap();
                thread::sleep(Duration::from_millis(500));
                uart_handle.write("D\r\n".as_bytes()).unwrap();
            }
        }
    });

    // display
    let state_proxy_display = state.clone();
    thread::spawn(move || {
        loop {
            display_job_notifier_rx.recv().unwrap();
            {
                let localtime = Local::now();
                let state = state_proxy_display.lock().unwrap();
                display.clear();
                Text::new(localtime.format("%S").to_string().as_str(), Point::new(0, 96))
                    .into_styled(TextStyle::new(Font24x32, BinaryColor::On))
                    .draw(&mut display)
                    .unwrap();
                Text::new(format!("{:.1} C", state.ambient_temperature).as_str(), Point::zero())
                    .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
                    .draw(&mut display)
                    .unwrap();
                display.flush().unwrap();
            }
        }
    });

    // sensor
    let state_proxy_sensor = state.clone();
    thread::spawn(move || {
        loop {
            sensor_job_notifier_rx.recv().unwrap();
            {
                let bme280_res = bme280.measure().unwrap();
                let mut state = state_proxy_sensor.lock().unwrap();
                state.ambient_temperature = bme280_res.temperature;
            }
        }
    });

    // Assign periodic tasks
    scheduler.every(5.minute()).run(move || sensor_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.minute()).run(move || clock_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.second()).run(move || display_job_notifier_tx.send(()).unwrap());
    scheduler.every(1.second()).run(move || colon_blink_job_notifier_tx.send(()).unwrap());

    // Do the main loop
    loop {
        scheduler.run_pending();
        thread::sleep(Duration::from_millis(TICK_MS as u64));
    }
}
