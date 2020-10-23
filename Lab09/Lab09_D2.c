/*------------------------------------------------------------------------------
 * File:        Lab09_D2.c
 * Function:    Interfacing thumbstick
 * Description: This C program interfaces with a thumbstick sensor that has
 *              x (HORZ on Thumbstick connected to P6.0) and 
 *              y (VERT on Thumbstick connected to P6.1) axis 
 *              and outputs from 0 to 3V. A sample joystick can be found at
 *              https://www.digikey.com/htmldatasheets/production/2262974/0/0/1/512.html
 *              
 *              The value of x and y axis is sent as the percentage
 *              of por to the UAH Serial App.
 *
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal beten XIN & XOUT is required for ACLK
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |     P3.3/UCA0TXD|------------>
 *           P6.0(A0)-->|                 | 115200 - 8N1
 *           P6.1(A1)-->|     P3.4/UCA0RXD|<------------
 *                      |                 |
 * Input:       Connect thumbstick to the board
 * Output:      Displays % of por in UAH serial app
 * Author(s):   Prawar Poudel, prawar.poudel@uah.edu
 *              Micah Harvey
 * Date:        August 8, 2020
 *----------------------------------------------------------------------------*/
#include <msp430.h>

volatile long int ADCXval, ADCYval;
volatile float Xper, Yper;

void TimerA_setup(void)
{
    TA0CCTL0 = CCIE;                     // Enabled interrupt

    TA0CCR0 = 3277;                      // 3277 / 32768 Hz = 0.1s
    TA0CTL = TASSEL_1 + MC_1;            // ACLK, up mode
}


void ADC_setup(void)
{
    // configure ADC converter
    P6SEL = 0x07;                             // Enable A/D channel inputs
    ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8; // Turn on ADC12, extend sampling time
                                              // to avoid overflow of results

    ADC12CTL1 = ADC12SHP+ADC12CONSEQ_1;       // Use sampling timer, repeated sequence
    ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
    ADC12MCTL1 = ADC12INCH_1+ADC12EOS;        // ref+=AVcc, channel = A1, end seq.

    ADC12IE = 0x02;                           // Enable ADC12IFG.1
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
}


void UART_putCharacter(char c)
{
    while (!(UCA0IFG&UCTXIFG));    // Wait for previous character to transmit
    UCA0TXBUF = c;                  // Put character into tx buffer
}


void UART_setup(void)
{
    P3SEL |= BIT3 + BIT4;   // Set USCI_A0 RXD/TXD to receive/transmit data

    UCA0CTL1 |= UCSWRST;    // Set software reset during initialization
    UCA0CTL0 = 0;           // USCI_A0 control register
    UCA0CTL1 |= UCSSEL_2;   // Clock source SMCLK

    UCA0BR0 = 0x09;         // 1048576 Hz  / 115200 lower byte
    UCA0BR1 = 0x00;         // upper byte
    UCA0MCTL |= UCBRS0;     // Modulation (UCBRS0=0x01, UCOS16=0)

    UCA0CTL1 &= ~UCSWRST;   // Clear software reset to initialize USCI state machine
}


void sendData(void)
{
    int i;
    Xper = (ADCXval*3.0/4095*100/3);    // Calculate percentage outputs
    Yper = (ADCYval*3.0/4095*100/3);

    // Use character pointers to send one byte at a time
    char *xpointer=(char *)&Xper;
    char *ypointer=(char *)&Yper;

    UART_putCharacter(0x55);            // Send header
    for(i = 0; i < 4; i++)
    {            // Send x percentage - one byte at a time
        UART_putCharacter(xpointer[i]);
    }
    for(i = 0; i < 4; i++)
    {            // Send y percentage - one byte at a time
        UART_putCharacter(ypointer[i]);
    }
}


void main(void)
{
    WDTCTL = WDTPW +WDTHOLD;            // Stop WDT

    // Enable interrupts globally
    __enable_interrupt();

    ADC_setup();                        // Setup ADC
    UART_setup();
    TimerA_setup();

    while (1)
    {
        __bis_SR_register(LPM0_bits + GIE); // Enter LPM0
        sendData();
    }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
    ADCXval = ADC12MEM0;                  // Move results, IFG is cleared
    ADCYval = ADC12MEM1;
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerA_isr()
{
    ADC12CTL0 |= ADC12SC;
}
