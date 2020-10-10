;-------------------------------------------------------------------------------
; File		: Lab5_D2_RP.asm (CPE 325 Lab5 Demo code)
; Function	: Finds a sum of an input integer array
; Description: suma_rp is a subroutine that sums elements of an integer array
; Input	  : The input parameters are:
;					R12 -- array starting address
;					R13 -- the number of elements (>= 1)
; Output	 : The output result is returned in register R14
; Author	 : A. Milenkovic, milenkovic@computer.org
; Date		: September 14, 2008 (revised on August 2020)
;------------------------------------------------------------------------------
			.cdecls C,LIST,"msp430.h"	  ; Include device header file

			.def suma_rp

			.text

suma_rp:
			clr.w	R14			 ; clear register R14 (keeps the sum)
lnext:	  add.w	@R12+, R14	  ; add a new element
			dec.w	R13			 ; decrement step counter
			jnz	 lnext			; jump if not finished
lend:		ret					 ; return from subroutine

			.end
