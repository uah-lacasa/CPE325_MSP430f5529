/*------------------------------------------------------------------------------
 * File:        Lab01_D1.c
 * Function:    Calculate the factorial for first 15 integers
 * Description: This C program calculates the factorial for several integers
                and print out the result for both int (16-bit) and
                long int data types (32-bit), decimally and hexadecimally.
                
                Students must have the source file with definition of functions
                ifact() and lifact() added to the same project as this file.
 * Input:       MAXF
 * Output:      Factorials of integer numbers from 1 to MAXF
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 * Date:        Aug 16, 2017
 *----------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>

#define MAXF 16

int ifact(int);       // Prototype of ifact (integer)
long int lifact(int); // Prototype of lifact (long interger)

int main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    int i;       // step counter
    int a;       // result for type int 
    long int b;  // result for type long int
    // Print header
    printf("( i)!   :  int-dec,  int-hex :   long int-dec,   long int-hex;\n");
    for (i = 1; i < MAXF; i++)
    {
        a = ifact(i);   // Call subroutine ifact to calculate factoriel
        b = lifact(i);  // Call subroutine lifact to caculate factoriel
        // Print output
        printf("(%2d)!   : %8d, %8x : %14ld, %14lx;\n", i, a, a, b, b);
    }
    return 0;
}
