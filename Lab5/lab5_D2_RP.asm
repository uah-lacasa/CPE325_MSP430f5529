;-------------------------------------------------------------------------------
; File       : Lab5_D2_RP.asm (CPE 325 Lab5 Demo code)
; Function   : Finds a sum of an input integer array
; Description: suma_rp is a subroutine that sums elements of an integer array
; Input      : The input parameters are:
;                   R12 -- array starting address
;                   R13 -- the number of elements (>= 1)
;                   R14 -- display ID (0 for P1&P2 and 1 for P3&P4)
; Output     : No output
; Author     : A. Milenkovic, milenkovic@computer.org
; Date       : September 14, 2008
;------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"      ; Include device header file

            .def suma_rp

            .text

suma_rp:
            push.w  R7              ; save the register R7 on the stack
            clr.w   R7              ; clear register R7 (keeps the sum)
lnext:      add.w   @R12+, R7       ; add a new element
            dec.w   R13             ; decrement step counter
            jnz     lnext           ; jump if not finished
            bit.w   #1, R14         ; test display ID
            jnz     lp34            ; jump on lp34 if display ID=1
            mov.b   R7, P1OUT       ; display lower 8-bits of the sum on P1OUT
            swpb    R7              ; swap bytes
            mov.b   R7, P2OUT       ; display upper 8-bits of the sum on P2OUT
            jmp     lend            ; skip to end
lp34:       mov.b   R7, P3OUT       ; display lower 8-bits of the sum on P3OUT
            swpb    R7              ; swap bytes
            mov.b   R7, P4OUT       ; display upper 8-bits of the sum on P4OUT
lend:       pop     R7              ; restore R7
            ret                     ; return from subroutine

            .end
