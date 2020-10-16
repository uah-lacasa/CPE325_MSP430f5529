/*------------------------------------------------------------------------------
 * File:        Lab07_D3.c
 * Function:    Blinking LED1 using software polling.
 * Description: This C program configures the WDT in interval timer mode and
 *              it is clocked with ACLK. The WDT sets the interrupt flag
 *              (WDTIFG) every 1s. LED1 is toggled by verifying if this flag
 *              is set or not. After it is detected as set, WDTIFG is cleared.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *              An external watch crystal beten XIN & XOUT is required for ACLK
 *
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                  /|\|               XIN|-
 *                   | |                  | 32kHz
 *                   --|RST           XOUT|-
 *                     |                  |
 *                     |              P1.0|-->LED1(RED)
 *                     |                  |
 * Input:       None
 * Output:      LED1 blinks at 0.5Hz frequency
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430.h>

#define REDLED 0x01             // Mask for BIT0 = 0000_0001b

void main(void)
{
    WDTCTL = WDT_ADLY_1000;     // 1 s interval timer
    P1DIR |= REDLED;            // Set P1.0 to output direction

    while(1)                    // Infinite loop
    {
        // Use software polling
        if ((SFRIFG1 & WDTIFG) == 1)
        {
            P1OUT ^= REDLED;
            SFRIFG1 &= ~WDTIFG; // Clear bit WDTIFG in IFG1
        }
    }
}
