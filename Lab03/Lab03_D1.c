/*------------------------------------------------------------------------------
 * File:        Lab03_D1.c
 * Function:    Turning on LED1
 * Description: This C program turns on LED1 by writing 1 (P1.0 = 1).
 * Clocks:              MSP-EXP430F5529LP
 *                    --------------------
 *                 /|\|                  |
 *                  | |                  |
 *                  --|RST               |
 *                    |              P1.0|-->LED1(RED)
 *                    |                  |
 * Input:       None
 * Output:      LED1 is turned on
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        
 * ---------------------------------------------------------------------------*/
#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    P1DIR |= 0x01;              // Set P1.0 to output direction (0000_0001b)
    P1OUT |= 0x01;              // Set P1OUT to 0000_0001b (LED1 is ON)
    while(1);                   // Infinite loop
}
