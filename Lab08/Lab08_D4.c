/*------------------------------------------------------------------------------
 * File:        Lab08_D4.c
 * Function:    Send floating data to Serial port
 * Description: UAH serial app expects lower byte first so send each byte at a
 *              time sending lowest byte first. Serial App can be downloaded at
 *              portal.mhealth.uah.edu/public/index.php/serial-port-application
 
 *              FOR PROPER OPERATION:
 *              In the UAH serial app, please do the following:
 *              1. In the "Active Session" tab, select the appropriate Com Port.
 *              2. Check the box that says "Enable Chart"
 *              3. In "Settings" tab, 
 *                 a. Number of Channels = 1
 *                    i. We are sending a single floating point number to plot
 *                 b. Packet Size = 5 bytes
 *                    i. 1 byte header and 4 bytes for the floating point number
 *                 c. Header = 85 or 0x55
 *                    i. Header byte we are sending at the beginning of each
 *                       packet from our program
 *                 d. In CH0, select Type = Single 32bit
 *                 e. Set the position to 1
 *                 f. Check Show on Graph
 * Instruction: Set the following parameters in putty/hyperterminal
 * Port:        COMx
 * Baud rate:   115200
 * Data bits:   8
 * Parity:      None
 * Stop bits:   1
 * Flow Ctrl:   None
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO
 *                      MSP-EXP430F5529LP
 *                     --------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |     P3.3/UCA0TXD|------------>
 *                      |                 | 115200 - 8N1
 *                      |     P3.4/UCA0RXD|<------------
 *                      |             P1.0|----> LED1
 * Input:       None
 * Output:      Ramp signal in UAH Serial app
 * Author(s):   Prawar Poudel, prawar.poudel@uah.edu
 * Date:        October 2018
 * ---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdint.h>

volatile float myData;

void UART_setup(void)
{
    P3SEL |= BIT3 + BIT4;       // Set USCI_A0 RXD/TXD to receive/transmit data
    UCA0CTL1 |= UCSWRST;        // Set software reset during initialization
    UCA0CTL0 = 0;               // USCI_A0 control register
    UCA0CTL1 |= UCSSEL_2;       // Clock source SMCLK

    UCA0BR0 = 0x09;             // 1048576 Hz  / 115200 lower byte
    UCA0BR1 = 0x00;             // upper byte
    UCA0MCTL = 0x02;            // Modulation (UCBRS0=0x01, UCOS16=0)

    // Clear software reset to initialize USCI state machine
    UCA0CTL1 &= ~UCSWRST;
}


void UART_putCharacter(char c)
{
    while (!(UCA0IFG&UCTXIFG)); // Wait for previous character to transmit
    UCA0TXBUF = c;              // Put character into tx buffer
}


int main()
{
    WDTCTL = WDT_ADLY_1000;
    UART_setup();               // Initialize USCI_A0 module in UART mode
    SFRIE1 |= WDTIE;            // Enable watchdog interrupts

    myData = 0.0;
    __bis_SR_register(LPM0_bits + GIE);
}

// Sends a ramp signal; amplitude of one period ranges from 0.0 to 9.9
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    char index = 0;
    // Use character pointers to send one byte at a time
    char *myPointer = (char* )&myData;

    UART_putCharacter(0x55);    // Send header
    for(index = 0; index < 4; index++)
    {    // Send 4-bytes of myData
        UART_putCharacter(myPointer[index]);
    }

    // Update myData for next transmission
    myData = (myData + 0.1);
    if(myData >= 10.0)
    {
        myData = 0.0;
    }
}
