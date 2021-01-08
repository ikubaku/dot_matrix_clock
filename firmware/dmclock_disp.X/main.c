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

#define B_FALSE 0
#define B_TRUE 1

#define MATRIX_WIDTH 20

struct DisplayState
{
    uint8_t selected_row;    // 1-indexed !!
    uint8_t clock_phase;
    uint8_t is_hsync;
    uint8_t pos_x_c;
    uint8_t pos_y_c;
    uint8_t is_dot_active;
    uint8_t vram[MATRIX_WIDTH];    // The bit[n] stores ROWn pixel.
};

struct DisplayState g_disp_state;
#define GET_PIXEL_FROM_GLOBAL_VRAM(x, y) ((g_disp_state.vram[x] & (1 << (y))) ? 1 : 0)

uint8_t g_is_pixel_pulse;

void initialize_global_state(void)
{
    g_disp_state.selected_row = 0;
    g_disp_state.clock_phase = 0;
    g_disp_state.is_hsync = 0;
    g_disp_state.pos_x_c = 0;
    g_disp_state.pos_y_c = 0;
    g_disp_state.is_dot_active = B_FALSE;
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

void do_dot_blink(void)
{
    if(g_disp_state.is_dot_active) {
        g_disp_state.is_dot_active = B_FALSE;
    } else {
        g_disp_state.is_dot_active = B_TRUE;
    }
    if(g_disp_state.is_dot_active) {
        PWM3_LoadDutyValue(65535 / 1024);
    } else {
        PWM3_LoadDutyValue(65535 / 8192);
    }
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
    initialize_global_state();
    
    // De-assert DCLR and release SHDN
    IO_nDCLR_SetHigh();
    IO_SHDN_SetLow();
    
    // Select the last row
    select_last_row();
    
    // Register the interrupt handlers
    // The pixel pulse timer
    TMR0_SetInterruptHandler(notify_pixel_pulse);
    // The row start timer
    TMR1_SetInterruptHandler(do_row_start);
    // debug: dot timer
    TMR3_SetInterruptHandler(do_dot_blink);
    
    // DEBUG: Set the initial patterns
    g_disp_state.vram[19] = 0b00000110;
    g_disp_state.vram[18] = 0b00011001;
    g_disp_state.vram[17] = 0b00101001;
    g_disp_state.vram[16] = 0b01001001;
    g_disp_state.vram[15] = 0b00000110;
    g_disp_state.vram[14] = 0b00110110;
    g_disp_state.vram[13] = 0b01001001;
    g_disp_state.vram[12] = 0b01001001;
    g_disp_state.vram[11] = 0b01001001;
    g_disp_state.vram[10] = 0b00110110;
    g_disp_state.vram[9] = 0b00000110;
    g_disp_state.vram[8] = 0b00011001;
    g_disp_state.vram[7] = 0b00101001;
    g_disp_state.vram[6] = 0b01001001;
    g_disp_state.vram[5] = 0b00000110;
    g_disp_state.vram[4] = 0b00000000;
    g_disp_state.vram[3] = 0b01000000;
    g_disp_state.vram[2] = 0b01111111;
    g_disp_state.vram[1] = 0b01000010;
    g_disp_state.vram[0] = 0b00000000;

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
        //__delay_ms(500);
    }
}

/**
 End of File
*/