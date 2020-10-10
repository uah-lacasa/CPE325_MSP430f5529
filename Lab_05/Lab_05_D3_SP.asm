;-------------------------------------------------------------------------------
; File		: Lab5_D3_SP.asm (CPE 325 Lab5 Demo code)
; Function	: Finds a sum of an input integer array
; Description: suma_sp is a subroutine that sums elements of an integer array
; Input	  : The input parameters are on the stack pushed as follows:
;				 starting address of the array
;				 array length
; Output	 : The result is returned through the stack
; Author	 : A. Milenkovic, milenkovic@computer.org
; Date		: September 14, 2008 (revised August 2020)
;------------------------------------------------------------------------------
			.cdecls C,LIST,"msp430.h"		; Include device header file

			.def	suma_sp

			.text
suma_sp:
											; save the registers on the stack
			push	R7					  ; save R7, temporal sum
			push	R6					  ; save R6, array length
			push	R4					  ; save R5, pointer to array
			clr.w	R7					  ; clear R7
			mov.w	10(SP), R6			  ; retrieve array length
			mov.w	12(SP), R4			  ; retrieve starting address
lnext:	  add.w	@R4+, R7				; add next element
			dec.w	R6					  ; decrement array length
			jnz	 lnext					; repeat if not done
			mov.w	R7, 8(SP)				; store the sum on the stack
lend:		pop	 R4					  ; restore R4
			pop	 R6					  ; restore R6
			pop	 R7					  ; restore R7
			ret							 ; return

			.end
