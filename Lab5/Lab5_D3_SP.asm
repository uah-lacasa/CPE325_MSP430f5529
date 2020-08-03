;-------------------------------------------------------------------------------
; File       : Lab5_D3_SP.asm (CPE 325 Lab5 Demo code)
; Function   : Finds a sum of an input integer array
; Description: suma_sp is a subroutine that sums elements of an integer array
; Input      : The input parameters are on the stack pushed as follows:
;                 starting addrress of the array
;                 array length
;                 display id
; Output     : No output
; Author     : A. Milenkovic, milenkovic@computer.org
; Date       : September 14, 2008
;------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

            .def    suma_sp

            .text
suma_sp:
                                            ; save the registers on the stack
            push    R7                      ; save R7, temporal sum
            push    R6                      ; save R6, array length
            push    R4                      ; save R5, pointer to array
            clr.w   R7                      ; clear R7
            mov.w   10(SP), R6              ; retrieve array length
            mov.w   12(SP), R4              ; retrieve starting address
lnext:      add.w   @R4+, R7                ; add next element
            dec.w   R6                      ; decrement array length
            jnz     lnext                   ; repeat if not done
            mov.w   8(SP), R4               ; get id from the stack
            bit.w   #1, R4                  ; test display id
            jnz     lp34                    ; jump to lp34 display id = 1
            mov.b   R7, P1OUT               ; lower 8 bits of the sum to P1OUT
            swpb    R7                      ; swap bytes
            mov.b   R7, P2OUT               ; upper 8 bits of the sum to P2OUT
            jmp     lend                    ; jump to lend
lp34:       mov.b   R7, P3OUT               ; lower 8 bits of ths sum to P3OUT
            swpb    R7                      ; swap bytes
            mov.b   R7, P4OUT               ; upper 8 bits of the sum to P4OUT
lend:       pop     R4                      ; restore R4
            pop     R6                      ; restore R6
            pop     R7                      ; restore R7
            ret                             ; return

            .end
