/*------------------------------------------------------------------------------
 * File:		twofact.c
 * Function:	Subroutines ifact and lifact for lab_01 demo 
 * Description:	This C code calculates the factorial of a given number
				ifact gives an int output; lifact gives a long int output.
 * Input:		Integer variable p
 * Output:		Factorial of input (integer and long integer)
 * Author(s):	Aleksandar Milenkovic, milenkovic@computer.org
 * Date:		Aug 16, 2017
 * ---------------------------------------------------------------------------*/
int ifact(int p)
{
	int j = 0;
	int t = 1;

	if(p==0 || p==1) return 1;		// factorial of 1 and 0 is = 1
	else
	{
		for(j=2; j<=p; j++) t=t*j;	// Do the factorial multiplication
		return t;
	}
}


long int lifact(int p)
{
	int j = 0;
	long int t = 1;

	if(p==0 || p==1) return 1;		// factorial of 1 and 0 is = 1
	else {
		for(j=2; j<=p; j++) t=t*j;	// Do the factorial multiplication
		return t;
	}
}
