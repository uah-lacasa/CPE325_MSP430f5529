/*------------------------------------------------------------------------------
 * File:		twofact.c
 * Function:	Subroutines ifact and lifact for lab_01 demo 
 * Description:	This C code calculates the factorial of a given number
				ifact gives an int output; lifact gives a long int output.
 * Input:		Integer variable base
 * Output:		Factorial of input (integer and long integer)
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 * ---------------------------------------------------------------------------*/
int ifact(int base)
{
	int counter, total = 1;
	if(base == 0 || base == 1)
		return 1;				// Factorial of 1 and 0 is = 1
	else
	{
		for(counter = 2; counter <= base; counter++)
			total *= counter;	// Factorial multiplication
		return total;
	}
}


long int lifact(int base)
{
	long int counter, total = 1;
	if(base == 0 || base == 1)
		return 1;				// Factorial of 1 and 0 is = 1
	else {
		for(counter = 2; counter <= base; counter++)
			total *= counter;	// Factorial multiplication
		return total;
	}
}
