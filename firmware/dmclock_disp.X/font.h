/* 
 * File:   font.h
 * Author: ikubaku
 *
 * Created on January 8, 2021, 6:11 PM
 */

#ifndef FONT_H
#define	FONT_H

#ifdef	__cplusplus
extern "C" {
#endif

    uint8_t font5x7[11][5] = {
        // Whitespace
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
        },
        // 0
        {
            0b00111110,
            0b01000001,
            0b01000001,
            0b01000001,
            0b00111110,
        },
        // 1
        {
            0b00000000,
            0b01000010,
            0b01111111,
            0b01000000,
            0b00000000,
        },
        // 2
        {
            0b01000010,
            0b01100001,
            0b01010001,
            0b01001001,
            0b01000110,
        },
        // 3
        {
            0b00100010,
            0b01000001,
            0b01001001,
            0b01001001,
            0b00110110,
        },
        // 4
        {
            0b00110000,
            0b00101100,
            0b00100010,
            0b01111111,
            0b00100000,
        },
        // 5
        {
            0b00101111,
            0b01001001,
            0b01001001,
            0b01001001,
            0b00111001,
        },
        // 6
        {
            0b00111000,
            0b01001100,
            0b01001010,
            0b01001001,
            0b00110000,
        },
        // 7
        {
            0b00000111,
            0b00000001,
            0b01100001,
            0b00011101,
            0b00000011,
        },
        // 8
        {
            0b00110110,
            0b01001001,
            0b01001001,
            0b01001001,
            0b00110110,
        },
        // 9
        {
            0b00000110,
            0b01001001,
            0b00101001,
            0b00011001,
            0b00001110,
        },
    };


#ifdef	__cplusplus
}
#endif

#endif	/* FONT_H */

