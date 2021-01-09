use std::error::Error;
use std::thread;
use std::time::Duration;
use std::sync::{Arc, Mutex};

use rppal::uart::{Parity, Uart};

use clokwerk::{Scheduler, TimeUnits};
use clokwerk::Interval::*;

use chrono::prelude::*;

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

fn main() -> Result<(), Box<dyn Error>> {
    // Initialize hardware access
    let uart = Uart::new(115200, Parity::None, 8, 1)?;
    let uart = Arc::new(Mutex::new(uart));

    // Initialize scheduler
    let mut scheduler = Scheduler::new();

    // Assign periodic tasks
    scheduler.every(1.minute()).run(create_clock_job(uart.clone()));
    scheduler.every(1.second()).run(create_colon_blink_job(uart.clone()));

    // Do the main loop
    loop {
        scheduler.run_pending();
        thread::sleep(Duration::from_millis(TICK_MS as u64));
    }
}
