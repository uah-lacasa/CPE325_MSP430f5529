/*------------------------------------------------------------------------------
 * File:        twofact.c
 * Function:    Subroutines int_fact and long_int_fact for Lab01 demo 
 * Description: This C code calculates the factorial of a given number
                int_fact gives an int output; long_int_fact gives a long int.
 * Input:       Integer variable base
 * Output:      Factorial of input (integer and long integer)
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 * Date:        Aug 16, 2017
 * ---------------------------------------------------------------------------*/
int ifact(int p)
{
    int j = 0;
    int t = 1;

    if(p==0 || p==1) return 1;    // factorial of 1 and 0 is = 1
    else
    {
        for(j=2; j<=p; j++) t=t*j;  // Do the factorial multiplication
        return t;
    }
}


long int lifact(int p)
{
    int j = 0;
    long int t = 1;

    if(p==0 || p==1) return 1;     // factorial of 1 and 0 is = 1
    else
    {
        for(j=2; j<=p; j++) t=t*j;   // Do the factorial multiplication
        return t;
    }
}