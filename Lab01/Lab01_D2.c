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

//function prototypes
long int exponential(int, int);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    int base = 12;
    int power = 4;              // the exponent, must be positive and 1 or greater
    long int answer = exponential(base, power);  // find the power
    printf("%d raised to the %d power is %ld", base, power, answer);
    return 0;
}

// This function recursively calculates an exponential, given a base and a power
long int exponential(int base, int power)
{
    long int answer;
    if (power > 1)              // if power > 1, call again
    {
        power--;
        answer = base*exponential(base, power);
    }
    else                        // else power = 1 and the answer is the base
    {
        answer = base;
    }
    return answer;
}