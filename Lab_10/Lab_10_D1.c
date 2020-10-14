/*------------------------------------------------------------------------------
 * File:        Lab10_D1.c (CPE 325 Lab10 Demo code)
 *
 * Function:    Measuring the temperature (MPS430F5529)
 *
 * Description: This C program samples the on-chip temperature sensor and
 *              converts the sampled voltage from the sensor to temperature in
 *              degrees Celsius and Fahrenheit. The converted temperature is
 *              sent to HyperTerminal over the UART by using serial UART.
 *
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 * Instructions:Set the following parameters in HyperTerminal
 *                  Port :        COM1
 *                  Baud rate :   115200
 *                  Data bits:    8
 *                  Parity:       None
 *                  Stop bits:    1
 *                  Flow Control: None
 *
 *                         MSP430F5529
 *                      -------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |     P3.3/UCA0TXD|------------>
 *                      |                 | 115200 - 8N1
 *                      |     P3.4/UCA0RXD|<------------
 *                      |                 |
 * Input:       Character Y or y or N or n
 *
 * Output:      Displays Temperature in Celsius and Fahrenheit in HyperTerminal
 * Author:      Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel
 *------------------------------------------------------------------------------*/

#include  <msp430.h>
#include  <stdio.h>

#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C

char ch;                   // Holds the received char from UART
unsigned char rx_flag;     // Status flag to indicate new char is received

char gm1[] = "Hello! I am an MSP430. Would you like to know my temperature? (Y|N)";
char gm2[] = "Bye, bye!";
char gm3[] = "Type in Y or N!";

long int temp;                      // Holds the output of ADC
long int IntDegF;                   // Temperature in degrees Fahrenheit
long int IntDegC;                   // Temperature in degrees Celsius

char NewTem[25];

void UART_setup(void)
{

    P3SEL |= BIT3 + BIT4;   // Set USCI_A0 RXD/TXD to receive/transmit data
    UCA0CTL1 |= UCSWRST;    // Set software reset during initialization
    UCA0CTL0 = 0;           // USCI_A0 control register
    UCA0CTL1 |= UCSSEL_2;   // Clock source SMCLK

    UCA0BR0 = 0x09;         // 1048576 Hz  / 115200 lower byte
    UCA0BR1 = 0x00;         // upper byte
    UCA0MCTL = 0x02;        // Modulation (UCBRS0=0x01, UCOS16=0)

    UCA0CTL1 &= ~UCSWRST;   // Clear software reset to initialize USCI state machine
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void UART_putCharacter(char c)
{
    while (!(UCA0IFG&UCTXIFG));    // Wait for previous character to transmit
    UCA0TXBUF = c;                  // Put character into tx buffer
}

void sendMessage(char* msg, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        UART_putCharacter(msg[i]);
    }
    UART_putCharacter('\n');        // Newline
    UART_putCharacter('\r');        // Carriage return
}

void ADC_setup(void)
{
    REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                              // ADC12_A ref control registers
    ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
                                              // Internal ref = 1.5V
    ADC12CTL1 = ADC12SHP;                     // enable sample timer
    ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
    ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
    __delay_cycles(100);                       // delay to allow Ref to settle
    ADC12CTL0 |= ADC12ENC;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;         // Stop watchdog timer
    UART_setup();                     // Setup USCI_A0 module in UART mode
    ADC_setup();                      // Setup ADC12

    rx_flag = 0;                      // RX default state "empty"
    _EINT();                          // Enable global interrupts
    while(1)
    {
        sendMessage(gm1, sizeof(gm1));// Send a greetings message

        while(!(rx_flag&0x01));       // Wait for input
        rx_flag = 0;                  // Clear rx_flag
        sendMessage(&ch, 1);          // Send received char

        // Character input validation
        if ((ch == 'y') || (ch == 'Y'))
        {

            ADC12CTL0 &= ~ADC12SC;
            ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

            _BIS_SR(CPUOFF + GIE);      // LPM0 with interrupts enabled

            //in the following equation,
            // ..temp is digital value read
            //..we are using double intercept equation to compute the
            //.. .. temperature given by temp value
            //.. .. using observations at 85 C and 30 C as reference
            IntDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30)) /
                    (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;

            IntDegF = IntDegC*(9/5.0) + 32.0;

            // Printing the temperature on HyperTerminal/Putty
            sprintf(NewTem, "T(F)=%ld\tT(C)=%ld\n", IntDegF, IntDegC);
            sendMessage(NewTem, sizeof(NewTem));
        }
        else if ((ch == 'n') || (ch == 'N'))
        {
            sendMessage(gm2, sizeof(gm2));
            break;                      // Get out
        }
        else
        {
            sendMessage(gm3, sizeof(gm3));
        }
    }                                   // End of while
    while(1);                           // Stay here forever
}

#pragma vector = USCI_A0_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
    ch = UCA0RXBUF;                 // Copy the received char
    rx_flag = 0x01;                 // Signal to main
    LPM0_EXIT;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    temp = ADC12MEM0;               // Move results, IFG is cleared
    _BIC_SR_IRQ(CPUOFF);            // Clear CPUOFF bit from 0(SR)
}
