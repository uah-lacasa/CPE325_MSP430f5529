/*------------------------------------------------------------------------------
 * File:        Lab10_D1.c
 * Function:    Blink LED1 and LED2
 * Description: This program blinks LED1 and LED2 in an infinite loop
 * Clocks:      ACLK = LFXT1 = 32768Hz,
 *              MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |             P4.7|- LED2
 *                      |             P1.0|- LED1
 *                      |                 |
 * Input:       None
 * Output:        
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 * Date:        October 2018
 * Modified:    Prawar Poudel, prawar.poudel@uah.edu
 * Date:        August 8, 2019
 * ---------------------------------------------------------------------------*/
#include <msp430.h> 

#define REDLED 0x01             // Mask for BIT0 = 0000_0001b
#define GREENLED 0x80           // Mask for BIT7 = 1000_0000b

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    P1DIR |= REDLED;
    P4DIR |= GREENLED;
    P1OUT = 0x01;
    unsigned int i = 0;
    while(1)                    // Infinite loop
    {
        P1OUT ^= REDLED;
        P4OUT ^= GREENLED;
        for(i = 0; i < 5000; i++);
    }
    return 0;
}
