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
global _g_npx_r, _g_npx_g, _g_npx_b

global _write_neopixel ; extern of bar function goes in the C source file
_write_neopixel:
    ; Green channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_g:
	; Send 8bits of signal
	; 0.8us of H and 0.4us of L on Mark
	; 0.4us; o.8us on Space
	BTFSS _g_npx_g, 7
	GOTO bit_not_set_g
	BSF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_h_start_g_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_g_s
	BCF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_l_start_g_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_g_s
	GOTO bit_next_g
    bit_not_set_g:
        BSF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_h_start_g_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_g_ns
	BCF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_l_start_g_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_g_ns
    bit_next_g:
        RLCF _g_npx_g, W
	MOVWF _g_npx_g, F
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_g

    ; Red channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_r:
	BTFSS _g_npx_r, 7
	GOTO bit_not_set_r
	BSF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_h_start_r_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_r_s
	BCF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_l_start_r_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_r_s
	GOTO bit_next_r
    bit_not_set_r:
        BSF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_h_start_r_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_r_ns
	BCF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_l_start_r_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_r_ns
    bit_next_r:
        RLCF _g_npx_r, W
	MOVWF _g_npx_r, F
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_r

    ; Blue channel
    MOVLW 8
    MOVWF _g_cnt_bit, F
    bit_start_b:
	BTFSS _g_npx_b, 7
	GOTO bit_not_set_b
	BSF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_h_start_b_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_b_s
	BCF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_l_start_b_s:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_b_s
	GOTO bit_next_b
    bit_not_set_b:
        BSF PORTC, 0
	MOVLW 1
	MOVWF _g_cnt_uwait, F
	wait_h_start_b_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start_b_ns
	BCF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_l_start_b_ns:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start_b_ns
    bit_next_b:
        RLCF _g_npx_b, W
	MOVWF _g_npx_b, F
	DECFSZ _g_cnt_bit, F
	GOTO bit_start_b
	
    RETURN
