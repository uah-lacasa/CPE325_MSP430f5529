/*------------------------------------------------------------------------------
 * File:        Lab01_D2.c
 * Function:    This C code will calculate the power of a given base.
 * Description: This program calculates the power of a given
 *              base using recursive function call.
 * Input:       None
 * Output:      Base raised to the given power.
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 * Date:        Aug 16, 2017
 * ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "msp430.h"

long int exponential(int, int); // Prototype of exponential

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    int base = 12;
    int power = 4;              // Exponent, must be greater than 1
    long int answer = exponential(base, power);  // Find the power
    printf("%d raised to the %d power is %ld", base, power, answer);
    return 0;
}

// This function recursively calculates an exponential, given a base and a power
long int exponential(int base, int power)
{
    long int answer = 0;
    if (power > 1)
    {
        power--;
        answer = base * exponential(base, power); // Call function again
    }
    else                        // Else, power = 1
    {
        answer = base;          // Answer is the base when power = 1
    }
    return answer;
}
