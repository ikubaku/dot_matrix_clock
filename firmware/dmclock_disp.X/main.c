/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.5
        Device            :  PIC18F25Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#include "font.h"

#define B_FALSE 0
#define B_TRUE 1

#define MATRIX_WIDTH 20

#define COM_RECV_BUFLEN 32

struct DisplayState
{
    uint8_t selected_row;    // 1-indexed !!
    uint8_t clock_phase;
    uint8_t is_hsync;
    uint8_t pos_x_c;
    uint8_t pos_y_c;
    uint8_t is_dot_active;
    uint8_t vram[MATRIX_WIDTH];    // The bit[n] stores ROWn pixel.
    uint8_t npxram[5][3];
};

struct CommandState
{
    uint8_t recv_buf[COM_RECV_BUFLEN];
    uint8_t recv_buf_idx;
};

struct DisplayState g_disp_state;
#define GET_PIXEL_FROM_GLOBAL_VRAM(x, y) ((g_disp_state.vram[x] & (1 << (y))) ? 1 : 0)

struct CommandState g_com_state;

uint8_t g_is_pixel_pulse;

uint8_t g_is_command_ready;

// Working memory for the assembly functions
volatile uint8_t g_cnt_bit;
volatile uint8_t g_cnt_uwait;
volatile uint8_t g_npx_r;
volatile uint8_t g_npx_g;
volatile uint8_t g_npx_b;

// Name the NeoPixel VRAM address so that indirect addressing in the assembly
// function won't be necessary
volatile const uint8_t * g_npx_0_r = &(g_disp_state.npxram[0][0]);
volatile const uint8_t * g_npx_0_g = &(g_disp_state.npxram[0][1]);
volatile const uint8_t * g_npx_0_b = &(g_disp_state.npxram[0][2]);
volatile const uint8_t * g_npx_1_r = &(g_disp_state.npxram[1][0]);
volatile const uint8_t * g_npx_1_g = &(g_disp_state.npxram[1][1]);
volatile const uint8_t * g_npx_1_b = &(g_disp_state.npxram[1][2]);
volatile const uint8_t * g_npx_2_r = &(g_disp_state.npxram[2][0]);
volatile const uint8_t * g_npx_2_g = &(g_disp_state.npxram[2][1]);
volatile const uint8_t * g_npx_2_b = &(g_disp_state.npxram[2][2]);
volatile const uint8_t * g_npx_3_r = &(g_disp_state.npxram[3][0]);
volatile const uint8_t * g_npx_3_g = &(g_disp_state.npxram[3][1]);
volatile const uint8_t * g_npx_3_b = &(g_disp_state.npxram[3][2]);
volatile const uint8_t * g_npx_4_r = &(g_disp_state.npxram[4][0]);
volatile const uint8_t * g_npx_4_g = &(g_disp_state.npxram[4][1]);
volatile const uint8_t * g_npx_4_b = &(g_disp_state.npxram[4][2]);

// Assembly function prototypes
extern void write_neopixel(void);

void initialize_global_state(void)
{
    g_disp_state.selected_row = 0;
    g_disp_state.clock_phase = 0;
    g_disp_state.is_hsync = 0;
    g_disp_state.pos_x_c = 0;
    g_disp_state.pos_y_c = 0;
    g_disp_state.is_dot_active = B_FALSE;
    
    g_com_state.recv_buf_idx = 0;
}

void select_last_row(void)
{
    g_disp_state.selected_row = 7;
    IO_ROW7_SetHigh();
}

void unselect_rows(void)
{
    g_disp_state.selected_row = 0;
    IO_ROW1_SetLow();
    IO_ROW2_SetLow();
    IO_ROW3_SetLow();
    IO_ROW4_SetLow();
    IO_ROW5_SetLow();
    IO_ROW6_SetLow();
    IO_ROW7_SetLow();
}

uint8_t select_next_row(void)
{
    if(g_disp_state.selected_row == 0) {
        // None enabled
        return B_FALSE;
    } else if(g_disp_state.selected_row == 7) {
        // Wrap the next selection
        g_disp_state.selected_row = 1;
    } else {
        g_disp_state.selected_row += 1;
    }
    
    switch(g_disp_state.selected_row) {
        case 1:
            IO_ROW7_SetLow();
            IO_ROW1_SetHigh();
            return B_FALSE;
        case 2:
            IO_ROW1_SetLow();
            IO_ROW2_SetHigh();
            return B_FALSE;
        case 3:
            IO_ROW2_SetLow();
            IO_ROW3_SetHigh();
            return B_FALSE;
        case 4:
            IO_ROW3_SetLow();
            IO_ROW4_SetHigh();
            return B_FALSE;
        case 5:
            IO_ROW4_SetLow();
            IO_ROW5_SetHigh();
            return B_FALSE;
        case 6:
            IO_ROW5_SetLow();
            IO_ROW6_SetHigh();
            return B_FALSE;
        case 7:
            IO_ROW6_SetLow();
            IO_ROW7_SetHigh();
            return B_TRUE;    // VSYNC
        default:
            // This should not happen
            return B_FALSE;
    }
}

void send_pixel(void)
{
    // The data is sampled at the rising-edge of the SCLK.
    if(g_disp_state.clock_phase) {
        // Falling-edge (update the DOUT)
        if(GET_PIXEL_FROM_GLOBAL_VRAM(g_disp_state.pos_x_c, g_disp_state.pos_y_c)) {
            IO_DOUT_SetHigh();
        } else {
            IO_DOUT_SetLow();
        }
        
        IO_SCLK_SetLow();
        g_disp_state.clock_phase = 0;
    } else {
        // Rising-edge (do not change anything except the clock signal)
        IO_SCLK_SetHigh();
        g_disp_state.clock_phase = 1;
    }
}

void set_digit(uint8_t digit, uint8_t font_id)
{
    size_t i;
    uint8_t * font;
    
    if(digit > 3) return;
    
    font = font5x7[font_id];
    for(i=0; i<5; i++) {
        g_disp_state.vram[5 * digit + i] = font[i];
    }
}

void activate_colon(void)
{
    g_disp_state.is_dot_active = B_TRUE;
    PWM3_LoadDutyValue(65535 / 1024);
}

void deactivate_colon(void)
{
    g_disp_state.is_dot_active = B_FALSE;
    PWM3_LoadDutyValue(65535 / 8192);
}

void set_npx_color(uint8_t id, uint8_t r, uint8_t g, uint8_t b)
{
    g_disp_state.npxram[id][0] = r;
    g_disp_state.npxram[id][1] = g;
    g_disp_state.npxram[id][2] = b;
}

void show_npx(void) {
    // Enter the critical section
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    
    g_npx_r = g_disp_state.npxram[4][0];
    g_npx_g = g_disp_state.npxram[4][1];
    g_npx_b = g_disp_state.npxram[4][2];
    write_neopixel();
    g_npx_r = g_disp_state.npxram[3][0];
    g_npx_g = g_disp_state.npxram[3][1];
    g_npx_b = g_disp_state.npxram[3][2];
    write_neopixel();
    g_npx_r = g_disp_state.npxram[2][0];
    g_npx_g = g_disp_state.npxram[2][1];
    g_npx_b = g_disp_state.npxram[2][2];
    write_neopixel();
    g_npx_r = g_disp_state.npxram[1][0];
    g_npx_g = g_disp_state.npxram[1][1];
    g_npx_b = g_disp_state.npxram[1][2];
    write_neopixel();
    g_npx_r = g_disp_state.npxram[0][0];
    g_npx_g = g_disp_state.npxram[0][1];
    g_npx_b = g_disp_state.npxram[0][2];
    write_neopixel();
    
    // Exit the critical section
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}

uint8_t command_cmp(char c) {
    return g_com_state.recv_buf[0] == (uint8_t)c;
}

// returns -1 on failure
int8_t ctoi(uint8_t c) {
    int16_t res;
    
    res = c - '0';
    if(res < 0 || 9 < res) {
        return -1;
    } else {
        return (int8_t)res;
    }
}

void send_to_uart(const uint8_t * buf, size_t len) {
    size_t i;
    
    while(!EUSART1_is_tx_ready());
    for(i=0; i<len; i++) {
        EUSART1_Write(buf[i]);
        while(!EUSART1_is_tx_done());
    }
}

void do_pixel_pulse(void)
{
    if(g_disp_state.is_hsync) {
        // Stop the pixel pulse timer(TMR0)
        TMR0_StopTimer();
        g_disp_state.is_hsync = B_FALSE;
        IO_DISP_SetHigh();
        // NOTE: This select_next_row selects the "current" row that we just
        // have send the data.
        // assert(g_state.pos_y_c == g_state.selected_row - 1);
        if(select_next_row()) {
            // VSYNC
            g_disp_state.pos_y_c = 0;
        } else {
            g_disp_state.pos_y_c += 1;
        }
    } else {
        send_pixel();
        if(g_disp_state.clock_phase) {
            // Step the x value of the current pixel position
            if(g_disp_state.pos_x_c == MATRIX_WIDTH - 1) {
                g_disp_state.pos_x_c = 0;
                // Clock the DISP pin on the next call
                IO_DISP_SetLow();
                g_disp_state.is_hsync = B_TRUE;
            } else {
                g_disp_state.pos_x_c += 1;
            }
        }
    }
}

void notify_pixel_pulse(void)
{
    g_is_pixel_pulse = B_TRUE;
}

void do_row_start(void)
{
    // Start the pixel pulse timer(TMR0)
    TMR0_StartTimer();
}

void do_uart_recv(void)
{
    if(EUSART1_is_rx_ready()) {
        uint8_t idx = g_com_state.recv_buf_idx;
        if(idx >= COM_RECV_BUFLEN) {
            // Buffer overflow
            idx = 0;
        }
        g_com_state.recv_buf[idx] = EUSART1_Read();
        
        // Check for the CRLF
        if(idx > 0) {
            if(g_com_state.recv_buf[idx-1] == '\r' && g_com_state.recv_buf[idx] == '\n') {
                g_is_command_ready = B_TRUE;
            }
        }
        g_com_state.recv_buf_idx = idx + 1;
    }
}

void process_command(void) {
    int8_t res;
    size_t i;
    
    if(command_cmp('H')) {
        send_to_uart("Hello!\r\n", 8);
    } else if(command_cmp('T')) {
        // THHMM\r\n
        if(g_com_state.recv_buf_idx == 7) {
            // 4 digits
            for(i=0; i<4; i++) {
                res = ctoi(g_com_state.recv_buf[i + 1]);
                if(res < 0) {
                    send_to_uart("??\r\n", 4);
                    return;
                } else {
                    set_digit(i, res + 1);
                }
            }
        } else {
            // Bad usage
            send_to_uart("??\r\n", 4);
        }
    } else if(command_cmp('A')) {
        activate_colon();
    } else if(command_cmp('D')) {
        deactivate_colon();
    } else {
        // Undefined commands
        send_to_uart("?\r\n", 3);
    }
}

void do_command(void)
{
    process_command();
    
    g_com_state.recv_buf_idx = 0;
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Initialize the global variables
    g_is_pixel_pulse = B_FALSE;
    g_is_command_ready = B_FALSE;
    initialize_global_state();
    
    // De-assert DCLR and release SHDN
    IO_nDCLR_SetHigh();
    IO_SHDN_SetLow();
    
    // Select the last row
    select_last_row();
    
    // Deactivale the colon
    deactivate_colon();
    
    // debug: Test NeoPixel driver APIs
    set_npx_color(0, 0x40, 0x00, 0x00);
    set_npx_color(1, 0x00, 0x40, 0x00);
    set_npx_color(2, 0x00, 0x00, 0x40);
    set_npx_color(3, 0x20, 0x20, 0x00);
    set_npx_color(4, 0x20, 0x20, 0x20);
    show_npx();
    
    // Register the interrupt handlers
    // The pixel pulse timer
    TMR0_SetInterruptHandler(notify_pixel_pulse);
    // The row start timer
    TMR1_SetInterruptHandler(do_row_start);
    // UART command receiver
    //EUSART1_SetRxInterruptHandler(do_uart_recv);
    
    // DEBUG: Set the initial patterns
    set_digit(0, 2);
    set_digit(1, 10);
    set_digit(2, 9);
    set_digit(3, 10);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        // Add your application code
        if(g_is_pixel_pulse) {
            g_is_pixel_pulse = B_FALSE;
            do_pixel_pulse();
        }
        do_uart_recv();
        if(g_is_command_ready) {
            g_is_command_ready = B_FALSE;
            do_command();
        }
        //__delay_ms(500);
    }
}

/**
 End of File
*/