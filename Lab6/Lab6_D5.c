/********************************************************************************
 *   File:        Lab6_D5.c
 *   Description: The program detects when SW2 is pressed and turns on LED1.
 *                LED1 is kept on as long as SW1 is pressed.
 *                P1_ISR is used to detect both SW2 presses and releases.
 *   Board:       EXP430F5529LP Experimenter Board
 *   Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO
 *
 *                 MSP430F5529
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
********************************************************************************/
#include  <msp430.h>

unsigned char SW2pressed = 0;       // SW2 status (0 not pressed, 1 pressed)

void main(void) {
    WDTCTL = WDTPW+WDTHOLD;         // Stop WDT
    P1DIR |= BIT0;                  // Set LED1 as output
    P1OUT = 0x00;                   // Clear LED1 status

    SW2pressed = 0;

    P1DIR &= ~BIT1;                //set the direction at SW2 as input
    P1REN |= BIT1;                 // Enable Pull-up resistor
    P1OUT |= BIT1;                 // Required for proper IO

    _EINT();                        // Enable interrupts
    P1IE |= BIT1;                   // P1IE.BIT1 interrupt enabled
    P1IES |= BIT1;                  // P1IES.BIT1 hi/low edge
    P1IFG &= ~BIT1;                 // P1IFG.BIT1 is cleared

    _BIS_SR(LPM0_bits + GIE);       // Enter LPM0(CPU is off); Enable interrupts
}

// Port 2 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void) {
    if (SW2pressed == 0) {
        SW2pressed = 1;
        P1OUT |= BIT0;                // LED1 is turned ON
        P1IFG &= ~BIT1;               // P1IFG.BIT0 is cleared
        P1IES &= ~BIT1;               // P1IES.BIT0 low/high edge
    } else if (SW2pressed == 1) {
        SW2pressed = 0;
        P1OUT &= ~BIT0;                // LED1 is turned ON
        P1IFG &= ~BIT1;                // P1IFG.BIT0 is cleared
        P1IES |= BIT1;                 // P1IES.BIT0 hi/low edge
    }
}
