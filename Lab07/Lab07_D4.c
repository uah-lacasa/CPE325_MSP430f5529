/*------------------------------------------------------------------------------
 * File:        Lab07_D4.c
 * Function:    Toggling signal using Timer_A2 in continuous mode
 * Description: In this C program, Timer_A2 is configured for continuous mode.
 *              In this mode, the timer TA2 counts from 0 to 0xFFFF (default).
 *              So, the counter period is 65,536*1/2^20 = 62.5ms when SMCLK is
 *              selected. The TA2.1 output signal is configured to toggle every
 *              time the counter reaches the maximum value, which corresponds to
 *              62.5ms. TA2.1 is multiplexed with the P2.4, and there is an
 *              extension header from this pin.
 *
 *              Thus the output frequency on P2.4 will be SMCLK/(2*65536)~8 Hz.
 *              Please note that once configured, the Timer_A toggles the signal
 *              in pin P2.4 automatically even when the CPU is in sleep mode.
 *              Please use oscillator to see this.
 *
 *              Using the Grove Boosterpack, you can hook-up the Buzzer to the
 *              J14 header. This connects the Signal Pin of buzzer to P2.4.
 *              The buzzer produces sound when the signal value is high
 *              and vice versa.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (2^20 Hz)
 *              An external watch crystal beten XIN & XOUT is required for ACLK
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                  /|\|              XIN |-
 *                   | |                  | 32kHz
 *                   --|RST           XOUT|-
 *                     |                  |
 *                     |        P2.4/TA2.1|-->Buzzer
 *                     |                  |
 * Input:       None
 * Output:      Toggle output at P2.4 at 8Hz frequency using hardware TA2
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        December 2008
 * ---------------------------------------------------------------------------*/
#include <msp430F5529.h>

void main(void)
{
    WDTCTL = WDTPW +WDTHOLD;  // Stop WDT

    P2DIR |= BIT4;            // P2.4 output (TA2.1)
    P2SEL |= BIT4;            // P2.4 special function (TA2.1 output)

    TA2CCTL1 = OUTMOD_4;      // TA2.1 output is in toggle mode
    TA2CTL = TASSEL_2 + MC_2; // SMCLK is clock source, Continuous mode

    _BIS_SR(LPM0_bits + GIE); // Enter Low Power Mode 0
}
