/*------------------------------------------------------------------------------
 * File:        Lab03_D3.c
 * Function:    Turning on LED1 when S1 is pressed
 * Description: This C program turns on LED1 connected to P1.0 when the S1 is
 *              pressed. S1 is connected to P2.1 and when it is pressed,
 *              P2IN, bit 1 is read as a logic 0 (check the schematic).
 *              To avoid faulty detection of button press,
 *              debouncing delay of 20ms is added before turning on the LED1.
 * Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO (~1 MHz)
 *                      MSP-EXP430F5529LP
 *                      -----------------
 *                   /|\|               |
 *                    | |               |
 *                    --|RST            |
 *                      |           P1.0|-->LED1(RED)
 *                      |           P4.7|<--LED2(GREEN)
 *                      |               |
 * Input:       Pressing S1
 * Output:      LED1 is turned on when S1 is pressed
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel, prawar.poudel@uah.edu
 * Date:        
 * ---------------------------------------------------------------------------*/
#include <msp430.h>

#define S1 P2IN&BIT1

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer
    P1DIR |= BIT0;                      // Set P1.0 to output direction (0000_0001b)
    P1OUT &= ~BIT0;                     // LED1 is OFF

    P2DIR &= ~BIT1;                     // Set P2.1 as input for S1 input
    P2REN |= BIT1;                      // Enable the pull-up resistor at P2.1
    P2OUT |= BIT1;                      // Required for proper IO

    unsigned int i = 0;
    for (;;)
    {
        if ((S1) == 0)                  // If S1 is pressed
        {
            for (i = 2000; i > 0; i--); // Debounce ~20 ms
            if ((S1) == 0)              // If S1 is pressed
            {
                P1OUT |= BIT0;          // Turn LED1 on
            }
            while ((S1) == 0);          // Hang-on as long as S1 pressed
        }
        else
		{
            P1OUT &= ~BIT0;             // Turn LED1 off
		}
    }
}
