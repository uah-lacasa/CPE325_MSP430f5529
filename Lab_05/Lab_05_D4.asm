;/******************************************************************************
 ;*  File:        Lab5_D4.asm
 ;*  Description: MSP430F5529 Demo: This program defines two integer variables
 ;*               .. and performs multiplication of these two intergers and
 ;*               .. and stores the result in another variable
 ;*
 ;*  Clocks:      ACLK = 32768Hz,
 ;*               MCLK = SMCLK = 1 Mhz
 ;*
 ;* Input:       None
 ;* Output:      None
 ;*
 ;*                MSP430F5529
 ;*            -----------------
 ;*        /|\|              XIN|-
 ;*         | |                 | 32kHz
 ;*         --|RST          XOUT|-
 ;*           |                 |
 ;*           |                 |
 ;*           |                 |
 ;*           |                 |
 ;*           |                 |
 ;*           |                 |
 ;*
 ;*  Modified:   Prawar Poudel
 ;*  Date:       August 2020
 ;****************************************************************************/

;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-----------------------------------------------------------------------------
;            USER DATA
;-----------------------------------------------------------------------------
            .data                            ; so that it goes to data section
val1:        .int    45                        ; val1 is an integer whose value is 45
val2:        .int    3                        ; val2 is an integer whose value is 3
val3:        .int    0                        ; val3 will hold result of val1*val2
                                            ; .. let us init it with 0 for now
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:
            mov val1,&MPY                ; moves val1 to R5
            mov val2,&OP2                ; moves val2 to R6

            ; since we have both the numbers already, let us get the results
            ; after three clock cycles (for 16X16 multiplication)
            nop
            nop
            nop

            mov  RESLO,&val3

            jmp $                        ; infinite loop

                                            

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
            
