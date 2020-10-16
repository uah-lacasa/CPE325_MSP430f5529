/*------------------------------------------------------------------------------
 * File:        Lab07_D6.c
 * Function:    Blinking LED1 & LED2 using Timer_A0 with interrupts
 * Description: In this C program, Timer_A0 is configured for up/down mode with
 *              ACLK source and interrupts for channel 0 and channel 1 are
 *              enabled. In up/down mode timer TA0 counts the value from 0 up to
 *              value stored in TA0CCR0 and then counts back to 0. The interrupt
 *              for TA0 is generated when the counter reaches value in TA0CCR0.
 *              The interrupt TA0.1 is generated whenever the counter reaches 
 *              value in TA0CCR1. Thus, TA0.1 gets two interrupts while counting
 *              upwards and counting downwards. This simulates a PWM control.
 *              Adjusting the TA0.1 and TA0.0 CCR register values adjusts the
 *              duty cycle of the PWM signal.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *              An external watch crystal beten XIN & XOUT is required for ACLK
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                  /|\|               XIN|-
 *                   | |                  | 32kHz
 *                   --|RST           XOUT|-
 *                     |                  |
 *                     |              P1.0|--> LED1(RED)
 *                     |              P4.7|--> LED2(GREEN)
 * Input:       None
 * Output:      LED1 blinks at 1.64Hz with 20-80% duty cycle and LED2 blinks at
 *              0.82Hz with 50-50% duty cycle.
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430F5529.h>

#define REDLED 0x01             // Mask for BIT0 = 0000_0001b
#define GREENLED 0x80           // Mask for BIT7 = 1000_0000b

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    _EINT();                    // Enable interrupts

    P1DIR |= REDLED;            // LED1 as output
    P4DIR |= GREENLED;          // LED2 as output

    P1OUT &= ~REDLED;           // ensure LED1 and LED2 are off
    P4OUT &= ~GREENLED;

    TA0CCTL0 = CCIE;            // TA0 count triggers interrupt
    TA0CCR0 = 10000;            // Set TA0 (and maximum) count value

    TA0CCTL1 = CCIE;            // TA0.1 count triggers interrupt
    TA0CCR1 = 2000;             // Set TA0.1 count value

    TA0CTL = TASSEL_1 | MC_3;   // ACLK is clock source, UP/DOWN mode

    _BIS_SR(LPM3);              // Enter Low Power Mode 3
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerISR(void)
{
    P4OUT ^= GREENLED;          // Toggle LED2
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timerISR2(void)
{
    P1OUT ^= REDLED;            // Toggle LED1
    TA0CCTL1 &= ~CCIFG;         // Clear interrupt flag
}
