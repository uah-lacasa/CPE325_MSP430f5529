;-------------------------------------------------------------------------------
; File: 		Lab5_D1.asm (CPE 325 Lab5 Demo code)
; Function: 	Finds a sum of two integer arrays
; Description: 	The program initializes ports,
;				sums up elements of two integer arrays and
;				display sums on on parallel port output registers
; Input: 		The input arrays are signed 16-bit integers in arr1 and arr2
; Output: 		P1OUT&P2OUT displays sum of arr1, P3OUT&P4OUT displays sum of arr2
; Author: 		A. Milenkovic, milenkovic@computer.org
; Date: 		September 14, 2008
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
RESET:		mov.w	#__STACK_END,SP			; Initialize stack pointer
StopWDT:	 mov.w	#WDTPW|WDTHOLD,&WDTCTL 	; Stop watchdog timer
;-------------------------------------------------------------------------------
; Main code here
;-------------------------------------------------------------------------------
main:
			; load the starting address of the array1 into the register R4
			mov.w	#arr1, R4
			; load the starting address of the array2 into the register R5
			mov.w	#arr2, R5
			; Sum arr1 and display
			clr.w	R7						; holds the sum
			mov.w	#8, R10					; number of elements in arr1
lnext1:	 add.w	@R4+, R7					; add the current element to sum
			dec.w	R10						; decrement arr1 length
			jnz	 lnext1						; get next element
			mov.b	R7, P1OUT				; display lor byte of sum of arr1
			swpb	R7						; swap bytes
			mov.b	R7, P2OUT				; display upper byte of sum of arr1
			; Sum arr2 and display
			clr.w	R7						; Holds the sum
			mov.w	#7, R10					; number of elements in arr2
lnext2:	 add.w	@R5+, R7					; get next element
			dec.w	R10						; decrement arr2 length
			jnz	 lnext2						; get next element
			mov.b	R7, P3OUT				; display lor byte of sum of arr2
			swpb	R7						; swap bytes
			mov.b	R7, P4OUT				; display upper byte of sum of arr2
			jmp	 $

arr1:		.int	1, 2, 3, 4, 1, 2, 3, 4	; the first array
arr2:		.int	1, 1, 1, 1, -1, -1, -1	; the second array

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
			.global __STACK_END
			.sect	.stack

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
			.sect	".reset"				; MSP430 RESET Vector
			.short	RESET
			.end
