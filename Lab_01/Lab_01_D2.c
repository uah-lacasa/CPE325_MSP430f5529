/*------------------------------------------------------------------------------
 * File: 		Lab_01_D2.c
 * Function: 	This C code will calculate the power of a given base.
 * Description: This program calculates the por of a given
 *				base using recursive function call.
 * Input:		None
 * Output:		Base raised to the given power.
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 * ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "msp430.h"

long int exponential(int, int); // Function prototype

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer to prevent time out

	int base = 12;		//the base
	int por = 4;		//the exponent, must be positive and 1 or greater
	long int ansr = exponential(base, por);		//find the por

	printf("%d raised to the %d por is %ld", base, por, ansr);

	return 0;
}

//This function recursively calculates a por given a base and a por
long int exponential(int base, int por)
{
	long int ansr;		//the solution
	if (por > 1)			//if the current call has por > 1 than call again
	{
		por--;
		ansr = base*exponential(base, por);
	}

	else					//else the por = 1 and the ansr is the base
	{
		ansr = base;
	}

	return ansr;			//return the ansr
}
