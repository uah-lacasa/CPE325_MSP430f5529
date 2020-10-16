/*------------------------------------------------------------------------------
 * File:        Lab02_D1.c
 * Function:    Prints decimal, hex, and octal representations of numbers
 * Description: This program demonstrates common C data types and
 *              printf formatting options.    
 * Input:       None
 * Output:      Console print statements
 * Author(s):   Aleksandar Milenkovic, milenkovic@computer.org
 * Date:        Aug 16, 2017
 * ---------------------------------------------------------------------------*/
#include <msp430.h> 
#include <stdio.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    int int_1 = 11;                         // Signed 16-bit integer
	int int_2 = -6;                         // Signed 16-bit integer
    unsigned int u_int_1 = 65535;           // Unsigned 16-bit integer
    long int long_1 = 100000;               // Signed 32-bit integer
    long int long_2 = -2;                   // Signed 32-bit integer
    char char_1 = 'A';                      // 8-bit character
    float float_1 = 1.25;                   // Single-precision floating-point
    // pointer_1 points to memory where float_1 is stored
    unsigned long int* pointer_1 = &float_1;
    unsigned long int long_3 = *pointer_1;  // Interpret float as long integer

    printf("Each variable below is printed in decimal, hex, and octal representations.\n");
    printf(" int_1 = %6d, %#04.4x, %#06o\n", int_1, int_1, int_1);
    printf(" int_2 = %6d, %#04.4x, %#06o\n", int_2, int_2, int_2);
    printf(" u_int_1 = %6u, %#04.4x, %#06o\n", u_int_1, u_int_1, u_int_1);
    printf(" long_1 = %ld, %#08.8lx, %#011lo\n", long_1, long_1, long_1);
    printf(" long_2 = %6ld, %#08.8lx, %#011lo\n", long_2, long_2, long_2);
    printf(" float_1 = %6.2f, %#08.8lx\n", float_1, long_3);
    printf(" char_1 = %c, %#02.2x, %#03o\n", char_1, char_1, char_1);
    printf("That's all folks\n");
    return 0;
}
