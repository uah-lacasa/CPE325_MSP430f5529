/*------------------------------------------------------------------------------
 * File:        Lab7_D6.c (CPE 325 Lab7 Demo code)
 *
 * Function:    Blinking LED1 & LED2 using Timer_A0 with interrupts (MPS430F5529)
 *
 * Description: In this C program, Timer_A0 is configured for up/down mode with
 *              ACLK source and interrupts for channel 0 and channel 1 are
 *              enabled. In up/down mode timer TA0 counts the value from 0 up to
 *              value stored in TA0CCR0 and then counts back to 0. The interrupt
 *              for TA0 is generated when the counter reaches value in TA0CCR0.
 *              The interrupt TA0.1 is generated whenever the counter reaches value
 *              in TA0CCR1. Thus, TA0.1 gets two interrupts while counting upwards
 *              and counting downwards. This simulates a PWM control - adjusting
 *              the TA0.1 and TA0.0 CCR register values adjusts the duty cycle of the
 *              PWM signal.
 *
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                          MSP430xG461x
 *                       -----------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |             P1.0|--> LED1(RED)
 *                      |             P4.7|--> LED2(GREEN)
 * Input:       None
 * Output:      LED1 blinks at 1.64Hz with 20-80% duty cycle and LED2 blinks at
 *              0.82Hz with 50-50% duty cycle.
 *
 * Author:      Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel
 *------------------------------------------------------------------------------*/
#include <msp430F5529.h>

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
    _EINT();                      // Enable interrupts

    P1DIR |= BIT0;                //LED1 as output
    P4DIR |= BIT7;                //LED2 as output

    P1OUT &= ~BIT0;               // ensure LED1 and LED2 are off
    P4OUT &= ~BIT7;

    TA0CCTL0 = CCIE;              // TA0 count triggers interrupt
    TA0CCR0 = 10000;              // Set TA0 (and maximum) count value

    TA0CCTL1 = CCIE;              // TA0.1 count triggers interrupt
    TA0CCR1 = 2000;               // Set TA0.1 count value

    TA0CTL = TASSEL_1 | MC_3;     // ACLK is clock source, UP/DOWN mode

    _BIS_SR(LPM3);                // Enter Low Power Mode 3
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerISR(void) {
    P4OUT ^= BIT7;                // Toggle LED2
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timerISR2(void) {
    P1OUT ^= BIT0;                // Toggle LED1
    TA0CCTL1 &= ~CCIFG;            // Clear interrupt flag
}
