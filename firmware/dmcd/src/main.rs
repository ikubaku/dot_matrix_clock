use std::error::Error;
use std::thread;
use std::time::Duration;
use std::sync::{Arc, Mutex};

use rppal::uart::{Parity, Uart};
use rppal::i2c::I2c;

use clokwerk::{Scheduler, TimeUnits};
use clokwerk::Interval::*;

use chrono::prelude::*;

use shared_bus::BusManagerStd;

use embedded_graphics::prelude::*;
use embedded_graphics::fonts::{Font6x8, Text};
use embedded_graphics::pixelcolor::BinaryColor;
use embedded_graphics::style::TextStyle;

use sh1106::prelude::*;
use sh1106::Builder;
use sh1106::displayrotation::DisplayRotation::Rotate90;

const TICK_MS: u32 = 10;

fn create_clock_job(uart: Arc<Mutex<Uart>>) -> Box<dyn FnMut() + Send> {
    Box::new(move || {
        let mut uart_handle = uart.try_lock().unwrap();
        let localtime = Local::now();
        uart_handle.write(format!("T{}\r\n", localtime.format("%H%M")).as_bytes()).unwrap();
    })
}

fn create_colon_blink_job(uart: Arc<Mutex<Uart>>) -> Box<dyn FnMut() + Send> {
    Box::new(move || {
        let mut uart_handle = uart.try_lock().unwrap();
        uart_handle.write("A\r\n".as_bytes()).unwrap();
        thread::sleep(Duration::from_millis(500));
        uart_handle.write("D\r\n".as_bytes()).unwrap();
    })
}

fn create_display_job<I2C>(i2c: &BusManagerStd<I2C>) -> Box<dyn FnMut() + Send + '_>
    where I2C: embedded_hal::blocking::i2c::Write + Send,
          <I2C as embedded_hal::blocking::i2c::Write>::Error : std::fmt::Debug,
{
    let mut display: GraphicsMode<_> = Builder::new().with_rotation(Rotate90).connect_i2c(i2c.acquire_i2c()).into();
    display.init().unwrap();
    display.flush().unwrap();

    Box::new(move || {
        let localtime = Local::now();
        display.clear();
        Text::new(localtime.format("%S").to_string().as_str(), Point::zero())
            .into_styled(TextStyle::new(Font6x8, BinaryColor::On))
            .draw(&mut display)
            .unwrap();
        display.flush().unwrap();
    })
}

fn main() -> Result<(), Box<dyn Error>> {
    // Initialize hardware access
    let uart = Uart::new(115200, Parity::None, 8, 1)?;
    let uart = Arc::new(Mutex::new(uart));
    let i2c = I2c::new()?;
    let i2c: &'static _ = shared_bus::new_std!(I2c = i2c).unwrap();

    // Initialize scheduler
    let mut scheduler = Scheduler::new();

    // Assign periodic tasks
    scheduler.every(1.minute()).run(create_clock_job(uart.clone()));
    scheduler.every(1.second()).run(create_display_job(i2c));
    scheduler.every(1.second()).run(create_colon_blink_job(uart.clone()));

    // Do the main loop
    loop {
        scheduler.run_pending();
        thread::sleep(Duration::from_millis(TICK_MS as u64));
    }
}
