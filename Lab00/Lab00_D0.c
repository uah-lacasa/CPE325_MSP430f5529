/*------------------------------------------------------------------------------
 * File:        Lab00_D0.c
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
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    P1DIR |= BIT0;              // Set LED1 as output
    P4DIR |= BIT7;              // Set LED2 as output
    P1OUT &= ~BIT0;             // Set the value of LED1 (P1.0) to 0 (OFF)
    P4OUT |= BIT7;              // Set the value of LED2 (P4.7) to 1 (ON)
    while(1)
    {
        P1OUT ^= BIT0;          // Toggle LED 1
        P4OUT ^= BIT7;          // Toggle LED 2
        __delay_cycles(100000); // Arbitrary delay of ~50 ms
    }
    return 0;
}
