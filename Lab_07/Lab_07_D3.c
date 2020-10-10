/*------------------------------------------------------------------------------
 * File:		Lab07_D3.c (CPE 325 Lab7 Demo code)
 * Function:	Blinking LED1 using software polling.
 * Description:	This C program configures the WDT in interval timer mode and
 *				it is clocked with ACLK. The WDT sets the interrupt flag (WDTIFG)
 *				every 1 s. LED1 is toggled by verifying whether this flag
 *				is set or not. After it is detected as set, the WDTIFG is cleared.
 * Clocks:		ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *				An external watch crystal between XIN & XOUT is required for ACLK
 *
 *						  MSP430F5529
 *					   -----------------
 *				   /|\|			  XIN|-
 *					| |				 | 32kHz
 *					--|RST		  XOUT|-
 *					  |				 |
 *					  |			 P1.0|-->LED1(RED)
 *					  |				 |
 * Input:		None
 * Output:		LED1 blinks at 0.5Hz frequency
 *
 * Author:		Aleksandar Milenkovic, milenkovic@computer.org
 * Revised by:	Prawar Poudel
 *------------------------------------------------------------------------------*/
#include <msp430.h>

void main(void)
{
	WDTCTL = WDT_ADLY_1000;			 // 1 s interval timer
	P1DIR |= BIT0;					  // Set P2.2 to output direction

	for (;;) {
		// Use software polling
		if ((SFRIFG1 & WDTIFG) == 1) {
			P1OUT ^= BIT0;
			SFRIFG1 &= ~WDTIFG;		 // Clear bit WDTIFG in IFG1
		}
	}
}
