;-------------------------------------------------------------------------------
;	File:		Lab6_D1.asm
;	Description: The program toggles LEDs periodically.
;				LED1 is initialized off, LED2 is initalized on.
;				Main program loop:
;					the SWDelay1 loop creates 1s delay before
;					toggling the LEDs (ON/OFF).
;
;	Clocks:	  ACLK = 32.768kHz, MCLK = SMCLK = default DCO = 2^20=1,048,576 Hz
;	Platform:	TI EXP430F5529LP Launchpad
;
;				 MSP430xF5529
;			 -----------------
;		 /|\|				 |
;		  | |				 |
;		  --|RST			  |
;			|			 P1.0|-->LED1(RED)
;			|			 P4.7|-->LED2(GREEN)
;
;	Author:	 Aleksandar Milenkovic, milenkovic@computer.org
;	Date:		September 14, 2018
;	Modified:	Prawar Poudel, August 08, 2019
;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;-------------------------------------------------------------------------------
			.cdecls C, LIST, "msp430.h"		; Include device header file
;-------------------------------------------------------------------------------
			.def	RESET					; Export program entry-point to
											; make it known to linker.
;-------------------------------------------------------------------------------
			.text							; Assemble into program memory.
			.retain							; Override ELF conditional linking
											; and retain current section.
			.retainrefs						; And retain any sections that have
											; references to current section.

;-------------------------------------------------------------------------------
RESET		mov.w	#__STACK_END,SP			; Initialize stackpointer
StopWDT	 	mov.w	#WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

SETUP:
			bis.b	#0x01,&P1DIR			; set P1.0 as output, 0'b0000 0001
			bis.b	#0x80,&P4DIR			; set P4.7 as output, 0'b1000 0000

			bic.b	#0x01,&P1OUT			; turn P1.0 OFF
			bis.b	#0x80,&P4OUT			; turn P4.7 ON
;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
InfLoop:
			mov.w #0xFFFF,R5	; move 0xFFFF to R5 which will be out counter
SWDelay1:
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop				 ; 13 NOPs + extra 3cc is a delay of 16cc
			nop				 ; so the total delay is 65535*16cc/2^20 ~ 1s
			nop
			nop
			nop
			dec.w R5					; 1cc
			jnz SWDelay1				; 2cc
			xor.b #0x01,&P1OUT			; toggle 1.0
			xor.b #0x80,&P4OUT			; toggle 4.7
			jmp InfLoop					; go to InfLoop
			nop

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
			.global __STACK_END
			.sect	.stack
			
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
			.sect	".reset"				; MSP430 RESET Vector
			.short  RESET
