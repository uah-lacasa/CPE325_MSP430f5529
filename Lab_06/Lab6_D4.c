/********************************************************************************
 *   File:        Lab6_D4.c
 *   Description: The program detects when S2 is pressed and turns on LED1.
 *                LED1 is kept on as long as S2 is pressed.
 *                P1_ISR is used to detect when S2 is pressed.
 *                Main program polls S2 and turns off when a release is detected.
 *   Board:       MSP-EXP430F5529LP Launchpad
 *   Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO
 *
 *                 MSP430F5529
 *            +-----------------+
 *            |                 |
 *            |                 |
 *            |                 |
 *            |                 |
 *            |             P1.0|--> LED1
 *            |             P1.1|<-- S2
 *
 *   Author:    Aleksandar Milenkovic, milenkovic@computer.org
 *   Date:      September 2010
 *   Modified:  Prawar Poudel, August 08, 2019
********************************************************************************/
#include  <msp430.h>
#define   S2 BIT1&P1IN              // S2 is P1IN&BIT1

void main(void) {
    WDTCTL = WDTPW+WDTHOLD;         // Stop WDT

    P1DIR |= BIT0;                  // Set LED1 as output
    P1OUT = 0x00;                   // Clear LED1

    P1DIR &= ~BIT1;                 // Set the direction at S2 as input
    P1REN |= BIT1;                  // Enable Pull-up resistor
    P1OUT |= BIT1;                  // Required for proper IO

    _EINT();                        // Enable interrupts

    P1IE |= BIT1;                   // P1.1 interrupt enabled
    P1IES |= BIT1;                  // P1.1 hi/low edge
    P1IFG &= ~BIT1;                 // P1.1 IFG cleared

    for(;;) {
        while((S2) == 0);           // Wait until S2 is released
        P1OUT &= ~BIT0;             // LED1 is turned off
    }
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void) {
    P1OUT |= BIT0;                // LED1 is turned ON
    P1IFG &= ~BIT1;               // P1.0 IFG cleared
}
