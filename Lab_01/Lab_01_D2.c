/*------------------------------------------------------------------------------
 * File: 		Lab_01_D2.c
 * Function: 	This C code will calculate the power of a given base.
 * Description: This program calculates the power of a given
 *				base using recursive function call.
 * Input:		None
 * Output:		Base raised to the given power.
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 * ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "msp430.h"

long int exponential(int, int); 			// Function prototype

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;				// Stop watchdog timer to prevent time out

	int base = 12;							// Base
	int power = 4;							// Exponent, must be greater than 1 
	long int ansr = exponential(base, power);	//find the power

	printf("%d raised to the %d power is %ld", base, power, ansr);

	return 0;
}

//This function recursively calculates a power given a base and a power
long int exponential(int base, int power)
{
	long int ansr;						// Solution
	if (power > 1)						//if the current call has power > 1 than call again
	{
		power--;
		ansr = base*exponential(base, power);
	}

	else					// else the power = 1 and the ansr is the base
	{
		ansr = base;
	}
	return ansr;			// return the ansr
}
