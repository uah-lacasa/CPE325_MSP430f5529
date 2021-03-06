; ------------------------------------------------------------------------------
; File:         Lab06_D3.asm
; Function:     Demonstrates press and release using S2 and LED1.
; Description:  The main program enables interrupts    from P1.BIT1 (S2) and
;               remains in an infinite loop doing nothing. P1_ISR implements
;               debouncing and waits for a S2 to be released.
; Clocks:       ACLK = 32.768kHz, MCLK = SMCLK = default DCO = 2^20=1,048,576 Hz
;                       MSP-EXP430F5529LP
;                      --------------------
;                   /|\|                  |
;                    | |                  | 
;                    --|RST               |
;                      |              P1.0|-->LED1(RED)
;                      |              P1.1|<--S2
;                      |                  |
;                      |                  |
; Input:        Pressing S2
; Output:       LED1 when S2 is pressed
; Author(s):    Aleksandar Milenkovic, milenkovic@computer.org
; Date:         September 14, 2018
; Modified:     Prawar Poudel, prawar.poudel@uah.edu
; Date:         August 08, 2019
; ------------------------------------------------------------------------------
        .cdecls C, LIST, "msp430.h"     ; Include device header file
;-------------------------------------------------------------------------------
        .def    RESET                   ; Export program entry-point to
                                        ; make it known to linker.
        .def    S2_ISR
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
Setup:
        bis.b   #0x01, &P1DIR           ; Set P1.0 to output direction 0000_0001
        bic.b   #0x01, &P1OUT           ; Set P1OUT to 0000_0001

        bic.b   #0x02, &P1DIR           ; SET P1.1 as input for S2
        bis.b   #0x02, &P1REN           ; Enable Pull-Up resister at P1.1
        bis.b   #0x02, &P1OUT           ; required for proper IO set up

        bis.w   #GIE, SR                ; Enable Global Interrupts
        bis.b   #0x02, &P1IE            ; Enable Port 1 interrupt from bit 1
        bis.b   #0x02, &P1IES           ; Set interrupt to call from hi to low
        bic.b   #0x02, &P1IFG           ; Clear interrupt flag

InfLoop:
        jmp     $                       ; Loop here until interrupt                                   
;----------------------------------------------------------------------------
; P1_0 (S2) interrupt service routine (ISR)
;----------------------------------------------------------------------------
S2_ISR: bic.b   #0x02, &P1IFG           ; Clear interrupt flag

ChkSW2: bit.b   #0x02, &P1IN            ; Check if S2 is pressed
        jnz     LExit                   ; If not zero, SW is not pressed, jump

Debounce:
        mov.w   #2000, R15              ; Set to (2000 * 10 cc )

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
        bit.b   #0x02, &P1IN            ; Verify S2 is still pressed
        jnz     LExit                   ; If not, wait for S2 press

LEDon:  bis.b   #0x01, &P1OUT           ; Turn on LED1

SW2wait:
        bit.b   #0x02, &P1IN            ; Test S2
        jz      SW2wait                 ; Wait until S2 is released
        bic.b   #001, &P1OUT            ; Turn off LED1

LExit:  reti                            ; Return from interrupt
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
        .sect   ".int47"                ; PORT1_VECTOR,
        .short  S2_ISR                  ; See the MSP430F5529.h header file
        .end
