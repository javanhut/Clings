// types2.c
//
// A `char` is just a small integer. The character 'A' has the code 65,
// 'B' is 66, and so on, so you can do arithmetic on characters.
//
// Replace `???` with an expression that uses `c` (not the literal 'C')
// to make `c` the letter two places after 'A'. The program should print:
//
//     C has code 67

#include <stdio.h>

int main(void)
{
    char c = 'A';

    c = c + 2;

    printf("%c has code %d\n", c, c);
    return 0;
}
