/*------------------------------------------------------------------------------
 * File:        Lab3_D3.c (CPE 325 Lab3 Demo code)
 * Function:    Turning on LED1 when SW1 is pressed (MPS430F5529)
 * Description: This C program turns on LED1 connected to P1.0 when the SW1 is
 *              pressed. SW1 is connected to P2.1 and when the switch is pressed
 *              it is logic 0 (check the schematic). To avoid faulty detection
 *              of switch press delay of 20ms is added before turning on the LED1.
 * Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO (~1 MHz)
 *
 *                           MSP430F552x
 *                       -----------------
 *                   /|\|                 |
 *                    | |                 |
 *                    --|RST              |
 *                      |             P1.0|-->LED1(RED)
 *                      |             P2.1|<-- SW1
 *                      |                 |
 * Input:       Press SW1
 * Output:      LED1 is turned on when SW1 is pressed
 * Authors:     Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel
 *------------------------------------------------------------------------------*/
#include <msp430.h>

#define SW1 P2IN&BIT1

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
    P1DIR |= BIT0;                        // Set P1.0 to output direction (0000_0001)
    P1OUT &= ~BIT0;                       // LED1 is OFF

    P2DIR &= ~BIT1;                       // Set P2.1 as input for SW1 input
    P2REN |= BIT1;                        // Enable the Pull-up resistor at P2.1
    P2OUT |= BIT1;                        // Required for proper IO

    unsigned int i = 0;
    for (;;) {                            // Infinite loop
        if ((SW1) == 0) {                 // If SW1 is pressed
            for (i = 2000; i > 0; i--);   // Debounce ~20 ms
            if ((SW1) == 0)
            {
                P1OUT |= BIT0;            // SW1 pressed, turn LED1 on
            }
            while((SW1)==0);              // Hang-on as long as SW1 pressed
        }else
            P1OUT &= ~BIT0;
    }
}