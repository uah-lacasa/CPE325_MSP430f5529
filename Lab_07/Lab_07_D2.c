final commit/*------------------------------------------------------------------------------
 * File:		Lab_07_D2.c
 * Function:	Toggling LED1 using WDT ISR
 * Description:	This C program configures the WDT in interval timer mode,
 *				clocked with SMCLK. The WDT is configured to give an
 *				interrupt for every 32ms. The WDT ISR is counted for 32 times
 *				(32*32.5ms ~ 1sec) before toggling LED1 to get 1 s on/off.
 *				The blinking frequency of LED1 is 0.5Hz.
 * Clocks:		ACLK = XT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *				An external watch crystal beten XIN & XOUT is required for ACLK
 *
 *					  MSP-EXP430F5529LP
 *					  -----------------
 *				   /|\|			  XIN|-
 *					| |				 | 32kHz
 *					--|RST		  XOUT|-
 *					  |				 |
 *					  |			 P1.0|-->LED1(RED)
 *					  |				 |
 * Input:		None
 * Output:		LED1 blinks at 0.5Hz frequency
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * 				Prawar Poudel, prawar.poudel@uah.edu
 * Date:		December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430.h>

void main(void)
{
	WDTCTL = WDT_MDLY_32;		// 32ms interval (default)
	P1DIR |= BIT0;				// Set P1.0 to output direction
	SFRIE1 |= WDTIE;			// Enable WDT interrupt

	_BIS_SR(LPM0_bits + GIE);	// Enter LPM0 with interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	static int i = 0;
	i++;
	if (i == 32)
	{				// 31.25 * 32 ms = 1s
		P1OUT ^= BIT0;			// Toggle P1.0 using exclusive-OR
								// 1s on, 1s off; period = 2s, f = 1/2s = 0.5Hz
		i = 0;
	}
}
