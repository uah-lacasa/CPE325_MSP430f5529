/*--------------------------------------------------------------------------------
 * File:          Lab8_D3.c
 * Function:      Displays real-time clock in serial communication client.
 * Description:   This program maintains real-time clock and sends time
 *                (10 times a second) to the workstation through
 *                a serial asynchronous link (UART).
 *                The time is displayed as follows: "sssss:tsec".
 *
 *                Baud rate divider with 1048576hz = 1048576/(16*9600) = ~6.8 [16 from UCOS16]
 * Clocks:        ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 1048576Hz
 * Instructions:  Set the following parameters in putty/hyperterminal
 * Port: COMx
 * Baud rate: 19200
 * Data bits: 8
 * Parity: None
 * Stop bits: 1
 * Flow Control: None
 *
 *        MSP430F5529
 *     -----------------
 * /|\ |            XIN|-
 *  |  |               | 32kHz
 *  |--|RST        XOUT|-
 *     |               |
 *     |   P3.3/UCA0TXD|------------>
 *     |               | 9600 - 8N1
 *     |   P3.4/UCA0RXD|<------------
 *     |           P1.0|----> LED1
 *
 * Author:      A. Milenkovic, milenkovic@computer.org
 * Date:        October 2018
--------------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>

// Current time variables
unsigned int sec = 0;              // Seconds
unsigned int tsec = 0;             // 1/10 second
char Time[8];                      // String to keep current time

void UART_setup(void)
{
    P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 6;                              // 1MHz 9600 (see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Mod. UCBRSx=0, UCBRFx=0,
                                              // over sampling
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void TimerA_setup(void)
{
    TA0CTL = TASSEL_2 + MC_1 + ID_3; // Select SMCLK/8 and up mode
    TA0CCR0 = 13107;                 // 100ms interval
    TA0CCTL0 = CCIE;                 // Capture/compare interrupt enable
}

void UART_putCharacter(char c)
{
    while (!(UCA0IFG&UCTXIFG));    // Wait for previous character to transmit
    UCA0TXBUF = c;                  // Put character into tx buffer
}

void SetTime(void)
{
    tsec++;
    if (tsec == 10
    {
        tsec = 0;
        sec++;
        P1OUT ^= BIT0;              // Toggle LED1
    }
}

void SendTime(void)
{
    int i;
    sprintf(Time, "%05d:%01d", sec, tsec);// Prints time to a string

    for (i = 0; i < sizeof(Time); i++)
    {  // Send character by character
        UART_putCharacter(Time[i]);
    }
    UART_putCharacter('\r');        // Carriage Return
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    UART_setup();                   // Initialize UART
    TimerA_setup();                 // Initialize Timer_B
    P1DIR |= BIT0;                  // P1.0 is output;

    while(1)
    {
        _BIS_SR(LPM0_bits + GIE);   // Enter LPM0 w/ interrupts
        SendTime();                 // Send Time to HyperTerminal/putty
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMERA_ISA(void)
{
    SetTime();                       // Update time
    _BIC_SR_IRQ(LPM0_bits);          // Clear LPM0 bits from 0(SR)
}
