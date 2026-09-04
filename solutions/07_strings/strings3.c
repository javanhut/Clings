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
    size_t len = strlen(s);

    for (size_t i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

int main(void)
{
    char word[] = "clings";

    reverse(word);

    printf("reversed: %s\n", word);
    return 0;
}
