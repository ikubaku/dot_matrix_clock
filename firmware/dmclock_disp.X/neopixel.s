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

global _write_neopixel ; extern of bar function goes in the C source file
_write_neopixel:
    MOVLW 24
    MOVWF _g_cnt_bit, F
    bit_start:
	; Send 24bits of mark signal
	; 0.8us of H and 0.4us of L
	BSF PORTC, 0
	MOVLW 5
	MOVWF _g_cnt_uwait, F
	wait_h_start:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_h_start
	BCF PORTC, 0
	MOVLW 2
	MOVWF _g_cnt_uwait, F
	wait_l_start:
	    NOP
	    DECFSZ _g_cnt_uwait, F
	    GOTO wait_l_start
	DECFSZ _g_cnt_bit, F
	GOTO bit_start
    RETURN
