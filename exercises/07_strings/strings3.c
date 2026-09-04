// strings3.c
//
// Implement `reverse` so that it reverses the string *in place*: swap the
// first and last characters, then the second and second-to-last, and so
// on until you meet in the middle. Expected output:
//
//     reversed: sgnilc

#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
    // TODO: reverse the characters of s in place.
    (void)s;
}

int main(void)
{
    char word[] = "clings";

    reverse(word);

    printf("reversed: %s\n", word);
    return 0;
}
