// strings1.c
//
// CONCEPT
// C has no string type. A "string" is an array of char whose end is
// marked by a zero byte, '\0', the *null terminator*. `char s[] = "hello"`
// is an array of SIX chars: h e l l o \0. Everything that handles
// strings (printf's %s, strlen, strcpy) walks forward until it finds that
// zero. A char array without a terminator is not a string, and passing
// it to a string function reads past its end.
//
// Two ways to measure:
//     sizeof(s)   bytes of the array, including the '\0'   -> 6
//     strlen(s)   characters before the '\0'                -> 5
// strlen is a function from <string.h> that counts at run time; sizeof is
// computed by the compiler and only knows about arrays, not about
// pointers (see arrays4).
//
// WHEN YOU USE THIS
// Sizing buffers: a copy of `s` needs strlen(s) + 1 bytes. Forgetting
// the + 1 is the classic one-byte overflow. Understanding the terminator
// is the key to every string function you will write or read.
//
// TASK
// The program reports 6 characters for "hello". Fix it, and make the
// second line print the number of bytes the array occupies.
//
// EXPECTED OUTPUT
//     hello has 5 characters
//     the array takes 6 bytes

#include <stdio.h>

int main(void)
{
    char greeting[] = "hello";

    printf("%s has %zu characters\n", greeting, sizeof(greeting));
    printf("the array takes %zu bytes\n", ???);
    return 0;
}
