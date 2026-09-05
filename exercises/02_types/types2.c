// types2.c
//
// CONCEPT
// A `char` is a small integer, and a character literal such as 'A' is just
// a number: the code of that character in the machine's character set. On
// every system you will meet that is ASCII, where 'A' is 65, 'B' is 66 and
// so on, and the digits '0'..'9' are 48..57, also consecutive.
//
// So arithmetic on characters is arithmetic on integers: 'A' + 1 is 66,
// which printed with %c is 'B'. And 'Z' - 'A' is 25. This is why you can
// convert a digit character to its value with `c - '0'`.
//
// WHEN YOU USE THIS
// Parsing numbers by hand, Caesar ciphers, checking whether a character is
// a letter (`c >= 'a' && c <= 'z'`), building lookup tables indexed by
// character. The <ctype.h> functions (isdigit, toupper, ...) do the common
// cases portably; write the arithmetic yourself when you need something
// they do not offer.
//
// TASK
// Replace `???` with an expression that computes the letter two places
// after `c` in the alphabet, and print its numeric code.
//
// EXPECTED OUTPUT
//     C has code 67
//     digit '7' has value 7

#include <stdio.h>

int main(void)
{
    char c = 'A';
    char later = ???;
    char digit = '7';

    printf("%c has code %d\n", later, later);
    printf("digit '%c' has value %d\n", digit, ???);
    return 0;
}
