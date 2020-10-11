/*------------------------------------------------------------------------------
 * File: 		Lab_01_D1.c
 * Function: 	Calculate the factorial for first 15 integers
 * Description: This C program calculates the factorial for several integers
				and print out the result for both int (16-bit) and
				long int data types (32-bit), decimally and hexadecimally.
 * Input: 		MAXF
 * Output: 		Factorials of integer numbers from 1 to MAXF
 * Author(s): 	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 *----------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>

#define MAXF 16

int int_fact(int);					// Prototype of int_fact
long int long_int_fact(int);		// Prototype of long_int_fact

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer to prevent time out
	int i, a;						// Step counter and result for type int 
	long int b;						// Result for type long int
	// Print header
	printf("( i)!	:  int-dec,  int-hex :	long int-dec,	long int-hex;\n");
	for (i = 1; i < MAXF; i++)
	{
		a = int_fact(i);			// Call subroutine int_fact
		b = long_int_fact(i);		// Call subroutine long_int_fact
		// Print output
		printf("(%2d)!	: %8d, %8x : %14ld, %14lx;\n", i, a, a, b, b);
	}
	return 0;
}
