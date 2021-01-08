/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.5
        Device            :  PIC18F25Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_ROW1 aliases
#define IO_ROW1_TRIS                 TRISAbits.TRISA0
#define IO_ROW1_LAT                  LATAbits.LATA0
#define IO_ROW1_PORT                 PORTAbits.RA0
#define IO_ROW1_WPU                  WPUAbits.WPUA0
#define IO_ROW1_OD                   ODCONAbits.ODCA0
#define IO_ROW1_ANS                  ANSELAbits.ANSELA0
#define IO_ROW1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_ROW1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_ROW1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_ROW1_GetValue()           PORTAbits.RA0
#define IO_ROW1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_ROW1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_ROW1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_ROW1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_ROW1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_ROW1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_ROW1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define IO_ROW1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set IO_ROW2 aliases
#define IO_ROW2_TRIS                 TRISAbits.TRISA1
#define IO_ROW2_LAT                  LATAbits.LATA1
#define IO_ROW2_PORT                 PORTAbits.RA1
#define IO_ROW2_WPU                  WPUAbits.WPUA1
#define IO_ROW2_OD                   ODCONAbits.ODCA1
#define IO_ROW2_ANS                  ANSELAbits.ANSELA1
#define IO_ROW2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_ROW2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_ROW2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_ROW2_GetValue()           PORTAbits.RA1
#define IO_ROW2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_ROW2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_ROW2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_ROW2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_ROW2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_ROW2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_ROW2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define IO_ROW2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set IO_ROW3 aliases
#define IO_ROW3_TRIS                 TRISAbits.TRISA2
#define IO_ROW3_LAT                  LATAbits.LATA2
#define IO_ROW3_PORT                 PORTAbits.RA2
#define IO_ROW3_WPU                  WPUAbits.WPUA2
#define IO_ROW3_OD                   ODCONAbits.ODCA2
#define IO_ROW3_ANS                  ANSELAbits.ANSELA2
#define IO_ROW3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_ROW3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_ROW3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_ROW3_GetValue()           PORTAbits.RA2
#define IO_ROW3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_ROW3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_ROW3_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_ROW3_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_ROW3_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_ROW3_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_ROW3_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define IO_ROW3_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set IO_ROW4 aliases
#define IO_ROW4_TRIS                 TRISAbits.TRISA3
#define IO_ROW4_LAT                  LATAbits.LATA3
#define IO_ROW4_PORT                 PORTAbits.RA3
#define IO_ROW4_WPU                  WPUAbits.WPUA3
#define IO_ROW4_OD                   ODCONAbits.ODCA3
#define IO_ROW4_ANS                  ANSELAbits.ANSELA3
#define IO_ROW4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_ROW4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_ROW4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define IO_ROW4_GetValue()           PORTAbits.RA3
#define IO_ROW4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_ROW4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_ROW4_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_ROW4_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define IO_ROW4_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define IO_ROW4_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define IO_ROW4_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define IO_ROW4_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set IO_ROW5 aliases
#define IO_ROW5_TRIS                 TRISAbits.TRISA4
#define IO_ROW5_LAT                  LATAbits.LATA4
#define IO_ROW5_PORT                 PORTAbits.RA4
#define IO_ROW5_WPU                  WPUAbits.WPUA4
#define IO_ROW5_OD                   ODCONAbits.ODCA4
#define IO_ROW5_ANS                  ANSELAbits.ANSELA4
#define IO_ROW5_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_ROW5_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_ROW5_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_ROW5_GetValue()           PORTAbits.RA4
#define IO_ROW5_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_ROW5_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_ROW5_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_ROW5_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_ROW5_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_ROW5_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_ROW5_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define IO_ROW5_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set IO_ROW6 aliases
#define IO_ROW6_TRIS                 TRISAbits.TRISA5
#define IO_ROW6_LAT                  LATAbits.LATA5
#define IO_ROW6_PORT                 PORTAbits.RA5
#define IO_ROW6_WPU                  WPUAbits.WPUA5
#define IO_ROW6_OD                   ODCONAbits.ODCA5
#define IO_ROW6_ANS                  ANSELAbits.ANSELA5
#define IO_ROW6_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_ROW6_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_ROW6_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_ROW6_GetValue()           PORTAbits.RA5
#define IO_ROW6_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_ROW6_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_ROW6_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_ROW6_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_ROW6_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_ROW6_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_ROW6_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define IO_ROW6_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set IO_ROW7 aliases
#define IO_ROW7_TRIS                 TRISAbits.TRISA6
#define IO_ROW7_LAT                  LATAbits.LATA6
#define IO_ROW7_PORT                 PORTAbits.RA6
#define IO_ROW7_WPU                  WPUAbits.WPUA6
#define IO_ROW7_OD                   ODCONAbits.ODCA6
#define IO_ROW7_ANS                  ANSELAbits.ANSELA6
#define IO_ROW7_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IO_ROW7_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IO_ROW7_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define IO_ROW7_GetValue()           PORTAbits.RA6
#define IO_ROW7_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define IO_ROW7_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define IO_ROW7_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define IO_ROW7_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define IO_ROW7_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define IO_ROW7_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define IO_ROW7_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define IO_ROW7_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RA7 procedures
#define RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define RA7_GetValue()              PORTAbits.RA7
#define RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define RA7_SetPullup()             do { WPUAbits.WPUA7 = 1; } while(0)
#define RA7_ResetPullup()           do { WPUAbits.WPUA7 = 0; } while(0)
#define RA7_SetAnalogMode()         do { ANSELAbits.ANSELA7 = 1; } while(0)
#define RA7_SetDigitalMode()        do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set IO_DOUT aliases
#define IO_DOUT_TRIS                 TRISBbits.TRISB1
#define IO_DOUT_LAT                  LATBbits.LATB1
#define IO_DOUT_PORT                 PORTBbits.RB1
#define IO_DOUT_WPU                  WPUBbits.WPUB1
#define IO_DOUT_OD                   ODCONBbits.ODCB1
#define IO_DOUT_ANS                  ANSELBbits.ANSELB1
#define IO_DOUT_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_DOUT_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_DOUT_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_DOUT_GetValue()           PORTBbits.RB1
#define IO_DOUT_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_DOUT_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_DOUT_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_DOUT_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_DOUT_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define IO_DOUT_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define IO_DOUT_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define IO_DOUT_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set IO_SCLK aliases
#define IO_SCLK_TRIS                 TRISBbits.TRISB2
#define IO_SCLK_LAT                  LATBbits.LATB2
#define IO_SCLK_PORT                 PORTBbits.RB2
#define IO_SCLK_WPU                  WPUBbits.WPUB2
#define IO_SCLK_OD                   ODCONBbits.ODCB2
#define IO_SCLK_ANS                  ANSELBbits.ANSELB2
#define IO_SCLK_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_SCLK_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_SCLK_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_SCLK_GetValue()           PORTBbits.RB2
#define IO_SCLK_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_SCLK_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_SCLK_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_SCLK_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_SCLK_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IO_SCLK_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IO_SCLK_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define IO_SCLK_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set IO_nDCLR aliases
#define IO_nDCLR_TRIS                 TRISBbits.TRISB3
#define IO_nDCLR_LAT                  LATBbits.LATB3
#define IO_nDCLR_PORT                 PORTBbits.RB3
#define IO_nDCLR_WPU                  WPUBbits.WPUB3
#define IO_nDCLR_OD                   ODCONBbits.ODCB3
#define IO_nDCLR_ANS                  ANSELBbits.ANSELB3
#define IO_nDCLR_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_nDCLR_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_nDCLR_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define IO_nDCLR_GetValue()           PORTBbits.RB3
#define IO_nDCLR_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_nDCLR_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define IO_nDCLR_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define IO_nDCLR_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define IO_nDCLR_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define IO_nDCLR_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define IO_nDCLR_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define IO_nDCLR_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set IO_DISP aliases
#define IO_DISP_TRIS                 TRISBbits.TRISB4
#define IO_DISP_LAT                  LATBbits.LATB4
#define IO_DISP_PORT                 PORTBbits.RB4
#define IO_DISP_WPU                  WPUBbits.WPUB4
#define IO_DISP_OD                   ODCONBbits.ODCB4
#define IO_DISP_ANS                  ANSELBbits.ANSELB4
#define IO_DISP_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_DISP_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_DISP_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_DISP_GetValue()           PORTBbits.RB4
#define IO_DISP_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_DISP_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_DISP_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_DISP_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_DISP_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_DISP_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_DISP_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define IO_DISP_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set IO_SHDN aliases
#define IO_SHDN_TRIS                 TRISBbits.TRISB5
#define IO_SHDN_LAT                  LATBbits.LATB5
#define IO_SHDN_PORT                 PORTBbits.RB5
#define IO_SHDN_WPU                  WPUBbits.WPUB5
#define IO_SHDN_OD                   ODCONBbits.ODCB5
#define IO_SHDN_ANS                  ANSELBbits.ANSELB5
#define IO_SHDN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_SHDN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_SHDN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_SHDN_GetValue()           PORTBbits.RB5
#define IO_SHDN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_SHDN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_SHDN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_SHDN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_SHDN_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_SHDN_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_SHDN_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IO_SHDN_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set IO_NPX aliases
#define IO_NPX_TRIS                 TRISCbits.TRISC0
#define IO_NPX_LAT                  LATCbits.LATC0
#define IO_NPX_PORT                 PORTCbits.RC0
#define IO_NPX_WPU                  WPUCbits.WPUC0
#define IO_NPX_OD                   ODCONCbits.ODCC0
#define IO_NPX_ANS                  ANSELCbits.ANSELC0
#define IO_NPX_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_NPX_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_NPX_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_NPX_GetValue()           PORTCbits.RC0
#define IO_NPX_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_NPX_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_NPX_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_NPX_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_NPX_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_NPX_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_NPX_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define IO_NPX_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/