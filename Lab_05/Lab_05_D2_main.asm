;-------------------------------------------------------------------------------
; File       : Lab5_D2_main.asm (CPE 325 Lab5 Demo code)
; Function   : Finds a sum of two integer arrays using a subroutine.
; Description: The program calls suma_rp to sum up elements of integer arrays and
;              then displays the sum on parallel ports.
;              Parameters to suma_rp are passed through registers, R12, R13.
;              The subroutine suma_rp return the result in register R14.
; Input      : The input arrays are signed 16-bit integers in arr1 and arr2
; Output     : P1OUT&P2OU displays sum of arr1, P3OUT&P4OUT displays sum of arr2
; Author     : A. Milenkovic, milenkovic@computer.org
; Date       : September 14, 2008 (revised August 2020)
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
            .ref    suma_rp
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET:      mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT:    mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
; Main code here
;-------------------------------------------------------------------------------
main:
            mov.w   #arr1, R12              ; put address into R12
            mov.w   #8, R13                 ; put array length into R13
            call    #suma_rp
            ; P1OUT is at address 0x02, P2OUT is address 0x03
            ; we can write the 16-bit result to both at the same time
            ; P2OUT contains the upper byte and P1OUT the lower byte
            mov.w   R14, &P1OUT             ; result goes to P2OUT&P1OUT

            mov.w   #arr2, R12              ; put address into R12
            mov.w   #7, R13                 ; put array length into R13
            mov.w   #1, R14                 ; display #0 (P3&P4)
            call    #suma_rp
            mov.w   R14, &P3OUT             ; result goes to P4OUT&P3OUT
            jmp     $

arr1:        .int     1, 2, 3, 4, 1, 2, 3, 4     ; the first array
arr2:        .int     1, 1, 1, 1, -1, -1, -1     ; the second array

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
