/********************************************************************************
 *   File:        ToggleLEDs.c
 *   Description: Program toggles LED1 and LED2 by
 *                xoring port pins inside of an infinite loop.
 *
 *   Board:       MSP-EXP430F5529 Experimenter Board
 *   Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO
 *
 *                 MSP430F5529
 *             -----------------
 *         /|\|                 |
 *          | |                 |
 *          --|RST              |
 *            |                 |
 *            |             P1.0|--> LED1
 *            |             P4.7|--> LED2
 *
 *   Author: Alex Milenkovich, milenkovic@computer.org
 *   Date:   September 2010
 *   Modified: Prawar Poudel, prawar.poudel@uah.edu
 *   Date:   November 2020
********************************************************************************/
#include  <msp430.h>

int main(void) {
   WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

   P1DIR |= BIT0;               // Set P1.0 to output direction (xxxx_xxx1) for LED1
   P4DIR |= BIT7;               // Set P4.7 to output direction (1xxx_xxxx) for LED2

   P1OUT |= BIT0;               // Set P1.0 ON (xxxx_xxx1) for LED1
   P4OUT &= ~BIT7;              // Set P4.7 OFF (0xxx_xxxx) for LED2

   for (;;) {
     unsigned int i;

     P1OUT ^= BIT0;             // toggle the LED1
     P4OUT ^= BIT7;             // toggle the LED2

     for(i = 0; i < 50000; i++); // Software delay (13 cc per iteration)
     /* Total delay on average 13 cc*50,000 = 750,000; 750,000 * 1us = 0.75 s */
   }
   return 0;
}
