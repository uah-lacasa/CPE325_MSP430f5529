/******************************************************************************
 *  File:        Lab6_D6.c
 *  Description: MSP430F5529 Demo - FLL+, Runs Internal DCO at 2.45MHz
 *               This program demonstrates setting the internal DCO to run at
 *               2.45MHz with auto-calibration by the FLL+ circuitry.
 *  Clocks:      ACLK = LFXT1 = 32768Hz,
 *               MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
 *               An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                MSP430F5529
 *            -----------------
 *        /|\|              XIN|-
 *         | |                 | 32kHz
 *         --|RST          XOUT|-
 *           |                 |
 *           |             P7.7|--> MCLK = 2.45MHz
 *           |                 |
 *           |             P2.2|--> SMCLK = 2.45MHz
 *           |             P1.0|--> ACLK = 32kHz
 *           |                 |
 *
 *  Author:     Aleksandar Milenkovic, milenkovic@computer.og
 *  Date:       September 2010
 *  Modified:   Prawar Poudel, August 2020
 ******************************************************************************/
#include  <msp430.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;      // Stop watchdog timer
  P1DIR |= BIT0;                            // ACLK set out to pins
  P1SEL |= BIT0;
  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;
  P7DIR |= BIT7;                            // MCLK set out to pins
  P7SEL |= BIT7;

  UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx

  // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  } while (SFRIFG1&OFIFG);                  // Test oscillator fault flag

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 |= 74;                            // Set DCO Multiplier for 8MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (74 + 1) * 32768 = 2.45MHz
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 2.45 MHz / 32,768 Hz = 76600 = MCLK cycles for DCO to settle
  __delay_cycles(76000);

  while(1);
}
