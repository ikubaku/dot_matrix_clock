use std::error::Error;
use std::thread;
use std::time::Duration;
use std::sync::{Arc, Mutex};

use rppal::uart::{Parity, Uart};

use clokwerk::{Scheduler, TimeUnits};
use clokwerk::Interval::*;

const TICK_MS: u32 = 10;

fn create_test_job(uart: Arc<Mutex<Uart>>) -> Box<dyn FnMut() + Send> {
    let mut counter: u32 = 0;

    Box::new(move || {
        let mut uart_handle = uart.try_lock().unwrap();
        uart_handle.write(format!("T{:04}\r\n", counter).as_bytes()).unwrap();
        counter += 1;
        if counter > 9999 {
            counter = 0;
        }
    })
}

fn main() -> Result<(), Box<dyn Error>> {
    // Initialize hardware access
    let uart = Uart::new(115200, Parity::None, 8, 1)?;
    let uart = Arc::new(Mutex::new(uart));

    // Initialize scheduler
    let mut scheduler = Scheduler::new();

    // Assign periodic tasks
    scheduler.every(1.second()).run(create_test_job(uart.clone()));

    // Do the main loop
    let uart = uart.clone();
    let mut cnt_millis = 0;
    let mut is_colon_on = false;
    loop {
        scheduler.run_pending();
        cnt_millis += TICK_MS;
        if cnt_millis > 500 {
            // Toggle colon
            let mut uart_handle = uart.try_lock().unwrap();
            is_colon_on = !is_colon_on;
            if is_colon_on {
                uart_handle.write("A\r\n".as_bytes())?;
            } else {
                uart_handle.write("D\r\n".as_bytes())?;
            }
            cnt_millis = 0;
        }
        thread::sleep(Duration::from_millis(TICK_MS as u64));
    }
}
