;-------------------------------------------------------------------------------
; File       : Lab5_D2_main.asm (CPE 325 Lab5 Demo code)
; Function   : Finds a sum of two integer arrays using subroutines
; Description: The program initializes ports and
;              calls suma_rp to sum up elements of integer arrays and
;              display sums on parallel ports.
;              Parameters to suma_rp are passed through registers, R12, R13, R14.
; Input      : The input arrays are signed 16-bit integers in arr1 and arr2
; Output     : P1OUT&P2OUT displays sum of arr1, P3OUT&P4OUT displays sum of arr2
; Author     : A. Milenkovic, milenkovic@computer.org
; Date       : September 14, 2008
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"           ; Include device header file

;-------------------------------------------------------------------------------
            .def    RESET                       ; Export program entry-point to
                                                ; make it known to linker.
            .ref    suma_rp
;-------------------------------------------------------------------------------
            .text                               ; Assemble into program memory.
            .retain                             ; Override ELF conditional linking
                                                ; and retain current section.
            .retainrefs                         ; And retain any sections that have
                                                ; references to current section.
;-------------------------------------------------------------------------------
RESET:      mov.w   #__STACK_END,SP             ; Initialize stack pointer
StopWDT:    mov.w   #WDTPW|WDTHOLD,&WDTCTL      ; Stop watchdog timer

;-------------------------------------------------------------------------------
; Main code here
;-------------------------------------------------------------------------------
main:       bis.b   #0xFF,&P1DIR            ; configure P1.x as output
            bis.b   #0xFF,&P2DIR            ; configure P2.x as output
            bis.b   #0xFF,&P3DIR            ; configure P3.x as output
            bis.b   #0xFF,&P4DIR            ; configure P4.x as output

            mov.w   #arr1, R12              ; put address into R12
            mov.w   #8, R13                 ; put array length into R13
            mov.w   #0, R14                 ; display #0 (P1&P2)
            call    #suma_rp

            mov.w   #arr2, R12              ; put address into R12
            mov.w   #7, R13                 ; put array length into R13
            mov.w   #1, R14                 ; display #0 (P3&P4)
            call    #suma_rp
            jmp     $

arr1:       .int     1, 2, 3, 4, 1, 2, 3, 4  ; the first array
arr2:       .int     1, 1, 1, 1, -1, -1, -1  ; the second array

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            .end
