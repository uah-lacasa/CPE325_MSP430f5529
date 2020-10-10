/*------------------------------------------------------------------------------
 * File:		Lab00_D0.c
 * Function:	Toggle blinking of LED1 and LED2 (MPS430F5529)
 * Description: This C program initializes LED1 and LED2 as output
 *				with values 0 and 1 respectively. In the while loop,
 *				it toggles the values with an arbitrary delay.
 * Clocks:		ACLK = 32.768kHz, MCLK = SMCLK = default DCO (~1 MHz)
 *						MSP-EXP430F5529LP
 *            		  --------------------
 *				   /|\|					|
 *					| |					|
 *					--|RST				|
 *					  |			 	P1.0|-->LED1(RED)
 *					  |			 	P4.7|-->LED2(GREEN)
 *					  |				 	|
 * Input:		None
 * Output:		LED1 and LED2 toggle blinking
 * Author(s): 	Aleksandar Milenkovic, milenkovic@computer.org		
				Prawar Poudel, prawar.poudel@uah.edu
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <msp430.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer to prevent time out

	P4DIR |= BIT7;				// Initialize LED1 as output
	P1DIR |= BIT0;				// Initialize LED2 as output

	// Initialize the values of outputs
	P4OUT |= BIT7;				// P4.7 as 1 (LED2 ON)
	P1OUT &= ~BIT0;				// P1.0 as 0 (LED1 OFF)

	while(1)				// Infinite loop
	{
		P4OUT ^= BIT7; 			// Toggle values on LEDS
		P1OUT ^= BIT0; 			// Toggle values on LEDS
		__delay_cycles(100000); 	// Delay
	}
	return 0;
}
