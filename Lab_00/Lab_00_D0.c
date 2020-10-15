/*------------------------------------------------------------------------------
 * File:        Lab_00_D0.c
 * Function:    Toggle blinking of LED1 and LED2 (MPS430F5529)
 * Description: This C program initializes LED1 and LED2 as output
 *              with values 0 and 1 respectively. In the while loop,
 *              it toggles the values with an arbitrary delay.
 * Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO (~1 MHz)
 *                      MSP-EXP430F5529LP
 *                    --------------------
 *                 /|\|                  |
 *                  | |                  |
 *                  --|RST               |
 *                    |              P1.0|-->LED1(RED)
 *                    |              P4.7|-->LED2(GREEN)
 *                    |                  |
 * Input:       None
 * Output:      LED1 and LED2 toggle blinking
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org        
                Prawar Poudel, prawar.poudel@uah.edu
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <msp430.h>

int main()
{

    // stop watchdog timer
    WDTCTL = WDTPW+WDTHOLD;

    // initialize LED1 and LED2 as output
    P4DIR |= BIT7;
    P1DIR |= BIT0;

    // initialize the values of outputs to
    // P4.7 as 1 (LED2 ON)
    // P1.0 as 0 (LED1 OFF)
    P4OUT |= BIT7;
    P1OUT &= ~BIT0;

    while(1)
    {
        // toggle values on each LEDS
        P4OUT ^= BIT7;
        P1OUT ^= BIT0;
        // arbitrary delays
        __delay_cycles(100000);
    }
    return 0;
}
