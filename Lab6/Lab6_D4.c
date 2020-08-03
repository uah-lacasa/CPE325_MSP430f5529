/********************************************************************************
 *   File:        Lab6_D4.c
 *   Description: The program detects when SW2 is pressed and turns on LED1.
 *                LED1 is kept on as long as SW2 is pressed.
 *                P1_ISR is used to detect when SW2 is pressed.
 *                Main program polls SW2 and turns off when a release is detected.
 *   Board:       EXP430F5529LP Experimenter Board
 *   Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO
 *
 *                 MSP430FG461x
 *            +-----------------+
 *            |                 |
 *            |                 |
 *            |                 |
 *            |                 |
 *            |             P1.0|--> LED1
 *            |             P1.1|<-- SW2
 *
 *   Author: Aleksandar Milenkovic, milenkovic@computer.org
 *   Date:   September 2010
 *   Modified: Prawar Poudel, August 08, 2019
********************************************************************************/
#include  <msp430.h>
#define   SW2 BIT1&P1IN             // SW2 is P1IN&BIT1

void main(void) {
    WDTCTL = WDTPW+WDTHOLD;         // Stop WDT

    P1DIR |= BIT0;                  // Set LED1 as output
    P1OUT = 0x00;                   // clear LED1

    P1DIR &= ~BIT1;                //set the direction at SW2 as input
    P1REN |= BIT1;                 // Enable Pull-up resistor
    P1OUT |= BIT1;                 // Required for proper IO

    _EINT();                        // enable interrupts

    P1IE |= BIT1;                   // P1.1 interrupt enabled
    P1IES |= BIT1;                  // P1.1 hi/low edge
    P1IFG &= ~BIT1;                 // P1.1 IFG cleared

    for(;;) {
        while((SW2) == 0);          // Wait until SW2 is released
        P1OUT &= ~BIT0;             // LED1 is turned off
    }
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void) {
    P1OUT |= BIT0;                // LED1 is turned ON
    P1IFG &= ~BIT1;               // P1.0 IFG cleared
}
