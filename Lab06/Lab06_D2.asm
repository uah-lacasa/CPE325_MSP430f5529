; ------------------------------------------------------------------------------
; File:         Lab06_D2.asm
; Function:     Demonstrates press and release using S1 and LED1.
; Description:  When an S1 press is detected, a software delay of 20 ms
;               is used to implement debouncing. The switch is checked
;               again, and if it's on, LED1 is turned on until S1 is released.
; Clocks:       ACLK = 32.768kHz, MCLK = SMCLK = default DCO = 2^20=1,048,576 Hz
;                       MSP-EXP430F5529LP
;                      --------------------
;                   /|\|                  |
;                    | |                  | 
;                    --|RST               |
;                      |              P1.0|-->LED1(RED)
;                      |              P2.1|<--S1
;                      |                  |
;                      |                  |
; Input:        Pressing S1
; Output:       LED1 when S1 is pressed
; Author(s):    Aleksandar Milenkovic, milenkovic@computer.org
; Date:         September 14, 2018
; Modified:     Prawar Poudel, prawar.poudel@uah.edu
; Date:         August 08, 2019
; ------------------------------------------------------------------------------
        .cdecls C, LIST, "msp430.h"     ; Include device header file
;-------------------------------------------------------------------------------
        .def    RESET                   ; Export program entry-point to
                                        ; make it known to linker.
;-------------------------------------------------------------------------------
        .text                           ; Assemble into program memory.
        .retain                         ; Override ELF conditional linking
                                        ; and retain current section.
        .retainrefs                     ; And retain any sections that have
                                        ; references to current section.
;-------------------------------------------------------------------------------
RESET:  mov.w   #__STACK_END,SP         ; Initialize stack pointer
        mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer
;-------------------------------------------------------------------------------
SetupP2:
        bis.b   #0x01, &P1DIR           ; Set P1.0 to output direction (0000_0001)
        bic.b   #0x01, &P1OUT           ; Set P1OUT to 0x0000_0001 (ensure LED1 is off)

        bic.b   #0x02, &P2DIR           ; SET P2.1 as input for SW1
        bis.b   #0x02, &P2REN           ; Enable Pull-Up resister at P2.1
        bis.b   #0x02, &P2OUT           ; required for proper IO set up

ChkSW1: bic.b   #0x01, &P1OUT
        bit.b   #0x02, &P2IN            ; Check if SW1 is pressed (0000_0010 on P1IN)
        jnz     ChkSW1                  ; If not zero, SW1 is not pressed
                                        ; loop and check again
Debounce:
        mov.w   #2000, R15              ; Set to (2000 * 10 cc = 20,000 cc)
SWD20ms:
        dec.w   R15                     ; Decrement R15
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        jnz     SWD20ms                 ; Delay over?
        bit.b   #0x02, &P2IN            ; Verify SW1 is still pressed
        jnz     ChkSW1                  ; If not, wait for SW1 press

LEDon:  bis.b   #0x01, &P1OUT           ; Turn on LED1
SW1wait:
        bit.b   #0x02, &P2IN            ; Test SW1
        jz      SW1wait                 ; Wait until SW1 is released
        bic.b   #0x01, &P1OUT            ; Turn off LED1
        jmp     ChkSW1                  ; Loop to beginning
        nop                               
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
