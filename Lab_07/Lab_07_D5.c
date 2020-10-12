/*------------------------------------------------------------------------------
 * File:		Lab_07_D5.c
 * Function:	Toggle signal using Timer_A2 in up mode
 * Description:	In this C program, Timer_A2 is configured for UP mode. In this
 *				mode, the timer TA2 counts from 0 up to value stored in TA2CCR0.
 *				So, the counter period is CCR0*1us. The TA2.1 output signal is
 *				configured to toggle every time the counter reaches the value
 *				in TA2CCR1. TA2.1 is multiplexed with the P2.4. Thus, the output
 *				frequency on P2.4 will be f = ACLK/(2*CCR0) = 0.5Hz. Please note
 *				that once configured, the Timer_A2 toggles the signal
 *				automatically even when the CPU is in sleep mode.
 *
 *				Using the same connection as in Lab7_D4.c, you should be able to
 *				hear Buzzer ON for 1s and OFF for 1s continuously.
 * Clocks:		ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *				An external watch crystal beten XIN & XOUT is required for ACLK
 *
 *					  MSP-EXP430F5529LP
 *					  -----------------
 *				   /|\|			  XIN|-
 *					| |				 | 32kHz
 *					--|RST		 XOUT|-
 *					  |				 |
 *					  |	   P2.4/TA2.1|--> Buzzer
 *					  |				 |
 * Input:		None
 * Output:		Toggle output at P2.4 at 0.5Hz frequency using hardware TA2
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * 				Prawar Poudel, prawar.poudel@uah.edu
 * Date:		December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430F5529.h>

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out

	P2DIR |= BIT4;				// P7.4 output
	P2SEL |= BIT4;				// P7.4 special function (TB0.2 output)

	TA2CCTL1 = OUTMOD_4;		// TB0.2 output is in toggle mode
	TA2CTL = TBSSEL_1 + MC_1;	// ACLK is clock source, UP mode
	TA2CCR0 = 32767;			// Value to count upto for Up mode

	_BIS_SR(LPM3_bits + GIE);	// Enter Low Por Mode 3
}
