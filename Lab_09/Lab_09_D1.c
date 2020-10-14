/******************************************************************************
 File:          Lab9_D1.c
 Function:      Blink Led1 and Led2
 Description:   This program blinks Led1 and Led2 in an infinite loop

 Clocks:        ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz

      MSP430f5529
     -----------------
 /|\ |            XIN|-
  |  |               | 32kHz
  |--|RST        XOUT|-
     |               |
     |           P4.7|- Led2
     |           P1.0|- Led1
     |               |

 Input:     None
 Authors:   A. Milenkovic,
 Modified: Prawar Poudel, August 8, 2019
******************************************************************************/
#include <msp430.h> 

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;
    P4DIR |= BIT7;

    P1OUT = 0x01;
    unsigned int i = 0;
    for(;;)
    {
        P1OUT ^= BIT0;
        P4OUT ^= BIT7;
        for(i = 0; i < 5000; i++);
    }

    return 0;
}
