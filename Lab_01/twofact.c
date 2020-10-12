final commit/*------------------------------------------------------------------------------
 * File:		twofact.c
 * Function:	Subroutines int_fact and long_int_fact for lab_01 demo 
 * Description:	This C code calculates the factorial of a given number
				int_fact gives an int output; long_int_fact gives a long int.
 * Input:		Integer variable base
 * Output:		Factorial of input (integer and long integer)
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 * ---------------------------------------------------------------------------*/
int int_fact(int base)
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


long int long_int_fact(int base)
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
