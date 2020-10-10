/*------------------------------------------------------------------------------
 * File:		Lab00_D0.c (CPE 325 Lab0 Demo code)
 * Function:	Toggle blinking of LED1 and LED2 (MPS430F5529)
 * Description: This C program initializes LED1 and LED2 as output
 *				with values 0 and 1 respectively. In the while loop,
 *				it toggles the values with an arbitrary delay.
 * Clocks:		ACLK = 32.768kHz, MCLK = SMCLK = default DCO (~1 MHz)
 *
 *							MSP430F552x
 *						-----------------
 *					/||					|
 *					| |					|
 *					--|RST				|
 *					  |			 	P1.0|-->LED1(RED)
 *					  |			 	P4.7|-->LED2(GREEN)
 *					  |				 	|
 * Input:		None
 * Output:		LED1 and LED2 toggle blinking
 * Authors:	 	Prawar Poudel, pp0030@uah.edu
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <msp430.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer to prevent time out

	// Initialize LED1 and LED2 as output
	P4DIR |= BIT7;
	P1DIR |= BIT0;

	// Initialize the values of outputs to
	// P4.7 as 1 (LED2 ON)
	// P1.0 as 0 (LED1 OFF)
	P4OUT |= BIT7;
	P1OUT &= ~BIT0;

	while(1)
	{
		// Toggle values on each LEDS
		P4OUT ^= BIT7;
		P1OUT ^= BIT0;
		// Arbitrary delays
		__delay_cycles(100000);
	}
	return 0;
}
