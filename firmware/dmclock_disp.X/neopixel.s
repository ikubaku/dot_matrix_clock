#include <xc.inc>

; When assembly code is placed in a psect, it can be manipulated as a
; whole by the linker and placed in memory.  
;
; In this example, barfunc is the program section (psect) name, 'local' means
; that the section will not be combined with other sections even if they have
; the same name.  class=CODE means the barfunc must go in the CODE container.
; PIC18's should have a delta (addressible unit size) of 1 (default) since they
; are byte addressible.  PIC10/12/16's have a delta of 2 since they are word
; addressible.  PIC18's should have a reloc (alignment) flag of 2 for any
; psect which contains executable code.  PIC10/12/16's can use the default
; reloc value of 1.  Use one of the psects below for the device you use:

; psect   barfunc,local,class=CODE,delta=2 ; PIC10/12/16
psect   neopixel_driver,local,class=CODE,reloc=2 ; PIC18

global _g_cnt_bit, _g_cnt_uwait
//global _g_npx_0_r, g_npx_0_g, g_npx_0_b
//global _g_npx_1_r, g_npx_1_g, g_npx_1_b
//global _g_npx_2_r, g_npx_2_g, g_npx_2_b
//global _g_npx_3_r, g_npx_3_g, g_npx_3_b
//global _g_npx_4_r, g_npx_4_g, g_npx_4_b

global _write_neopixel ; extern of bar function goes in the C source file
_write_neopixel:
    // Green channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_g:
	; Send 8bits of unmark signal
	; 0.8us of H and 0.4us of L
	BSF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_h_start_g:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_g
	BCF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_l_start_g:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_g
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_g

    // Red channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_r:
	; Send 8bits of unmark signal
	; 0.8us of H and 0.4us of L
	BSF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_h_start_r:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_r
	BCF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_l_start_r:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_r
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_r

    // Blue channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_b:
	; Send 8bits of mark signal
	; 0.8us of H and 0.4us of L
	BSF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_h_start_b:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_b
	BCF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_l_start_b:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_b
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_b
    RETURN
