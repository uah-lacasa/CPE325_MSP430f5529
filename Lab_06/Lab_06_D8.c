/*------------------------------------------------------------------------------
 * File:		Lab_06_D8.c
 * Function:	This program demonstrates setting the internal DCO to run at
 *				8MHz when SW1 is pressed. Runs Internal DCO at 1MHz.
 * Description:	A LED will keep blinking at 1Hz (0.5s ON and 0.5s OFF) at
 *				clock running at default frequency of 1Mhz. When SW1 is pressed,
 *				the frequency is changed to ~ 8 Mhz. When SW1 is pressed again,
 *				the frequency is restored to 1Mhz.
 * Clocks:	  	ACLK = 32.768kHz
 * 				MCLK = SMCLK = DCO = (249+1) x ACLK = 8192000Hz
 * 						MSP-EXP430F5529LP
 *					  	------------------
 *				   /|\|				 XIN|-
 *		 			| |				 	| 32kHz
 *		 			--|RST		 	XOUT|-
 *					  |				 	|
 *	 			SW1-->|P2.1		 	P7.7|--> MCLK = 1 or 8MHz
 *			   LED2<--|P4.7			 	|
 *					  |			 	P2.2|--> SMCLK = 1 or 8MHz
 *					  |			 	P1.0|--> ACLK = 32kHz
 *					  |				    |
 * Input:		SW1 (P2.1)
 * Output:		LED2 (P4.7)
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		September 2010
 * Modified:	Prawar Poudel, prawar.poudel@uah.edu
 * Date:		August 2020
 * ---------------------------------------------------------------------------*/
#include  <msp430.h>

// this function configures the clock sources as follows
// .. use internal REFOCLK for FLL reference clock (UCSCTL3 = SELREF_2)
// .. ACLK is sourced with REFOCLK (UCSCTL4 |= SELA_2)
// .. sets DCO tap to 0 (UCSCTL0 = 0)
// .. sets the modulation bit counter value to 0 (UCSCTL0 = 0)
void configure_clock_sources();
inline void change_clock_freq_8Mhz();	// changes the clock frequency to 8 MHZ
inline void change_clock_freq_1Mhz();	// changes the clock frequency to 1 MHZ

char is8Mhz = 0;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer to prevent time out

	P1DIR |= BIT0;					// ACLK set out to pins
	P1SEL |= BIT0;

	P2DIR |= BIT2;					// SMCLK set out to pins
	P2SEL |= BIT2;

	P7DIR |= BIT7;					// MCLK set out to pins
	P7SEL |= BIT7;

	_EINT();						// enable interrupts
	P2DIR &= ~BIT1;					// set P2.1 as input (SW1)
	P2REN |= BIT1;					// enable pull-up resistor
	P2OUT |= BIT1;
	P2IE |= BIT1;					// enable interrupt at P2.1
	P2IES |= BIT1;					// enable hi->lo edge for interrupt
	P2IFG &= ~BIT1;					// clear any errornous interrupt flag

	P4DIR |= BIT7;					// set P4.7 as output (LED2)

	configure_clock_sources();		// configure the clock sources

	while(1)						// Infinite loop
	{
		P4OUT ^= BIT7;				// toggle LED2
		__delay_cycles(500000);		// arbitrary delay of 500ms
	}
}

// this ISR handles the SW1 key press
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	P2IFG &= ~BIT1;			// Clears the flag

	__delay_cycles(25000); 	// Debouncing

	if((P2IN&BIT1)!=0x00)	// if SW1 is not pressed
		return;

	if(is8Mhz==0)			// if not at 8Mhz, change to 8Mhz
	{
		change_clock_freq_8Mhz();
		is8Mhz = 1;
	}
	else 					// if at 8Mhz, change to 1Mhz
	{
		change_clock_freq_1Mhz();
		is8Mhz = 0;
	}
}

// this function changes the frequency of clock to 8 MHZ
void change_clock_freq_8Mhz()
{
	__bis_SR_register(SCG0);				// Disable the FLL control loop
	UCSCTL1 = DCORSEL_5;					// Select DCO range 8MHz operation
	UCSCTL2 = 249;							// Set DCO Multiplier for 8MHz
											// (N + 1) * FLLRef = Fdco
											// (249 + 1) * 32768 = 8MHz
	__bic_SR_register(SCG0);				// Enable the FLL control loop

	// Worst-case settling time for the DCO when the DCO range bits have been
	// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	// UG for optimization.
	// 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
	__delay_cycles(250000);
}

// this function changes the frequency of clock to 1 MHZ
void change_clock_freq_1Mhz()
{
	__bis_SR_register(SCG0);				// Disable the FLL control loop
	UCSCTL1 = DCORSEL_3;					// Select DCO range 1MHz operation
	UCSCTL2 = 32;							// Set DCO Multiplier for 1MHz
											// (N + 1) * FLLRef = Fdco
											// (32 + 1) * 32768 = 1MHz
	__bic_SR_register(SCG0);				// Enable the FLL control loop

	// Worst-case settling time for the DCO when the DCO range bits have been
	// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	// UG for optimization.
	// 32 x 32 x 1 MHz / 32,768 Hz = 33792 = MCLK cycles for DCO to settle
	__delay_cycles(33792);
}


// this function configures the clock sources as follows
// .. use internal REFOCLK for FLL reference clock (UCSCTL3 = SELREF_2)
// .. ACLK is sourced with REFOCLK (UCSCTL4 |= SELA_2)
// .. sets DCO tap to 0 (UCSCTL0 = 0)
// .. sets the modulation bit counter value to 0 (UCSCTL0 = 0)
void configure_clock_sources()
{
	UCSCTL3 = SELREF_2;						// Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_2;						// Set ACLK = REFO
	UCSCTL0 = 0x0000;						// Set lost possible DCOx, MODx

// Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
	do
	{
	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);	// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;							// Clear fault flags
	} while (SFRIFG1&OFIFG);					// Test oscillator fault flag
}
