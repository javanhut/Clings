// types2.c - solution

#include <stdio.h>

int main(void)
{
    char c = 'A';
    char later = c + 2;
    char digit = '7';

    printf("%c has code %d\n", later, later);
    printf("digit '%c' has value %d\n", digit, digit - '0');
    return 0;
}
