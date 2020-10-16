/*------------------------------------------------------------------------------
 * File:        Lab07_D1.c
 * Function:    Blinking LED1 using WDT ISR
 * Description: This C program configures the WDT in interval timer mode,
 *              clocked with the ACLK clock. The WDT is configured to give an
 *              interrupt for every 1s. LED1 is toggled in the WDT ISR
 *              by xoring P1.0. The blinking frequency of LED1 is 0.5Hz.
 * Clocks:      ACLK = XIN-XOUT = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal beten XIN & XOUT is required for ACLK
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz crystal
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |             P1.0|-->LED1(RED)
 *                      |                 |
 * Input:       None
 * Output:      LED1 blinks at 0.5Hz frequency
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430.h>

void main(void)
{
    WDTCTL = WDT_ADLY_1000;           // 1 s interval timer
    P1DIR |= BIT0;                    // Set P1.0 to output direction
    SFRIE1 |= WDTIE;                  // Enable WDT interrupt
    _BIS_SR(LPM0_bits + GIE);         // Enter LPM0 w/ interrupt
}

// Watchdog Timer Interrupt Service Routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    P1OUT ^= BIT0;                    // Toggle P1.0 using exclusive-OR
}
