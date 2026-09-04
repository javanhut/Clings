// strings1.c
//
// A C string is an array of characters that ends with a '\0' byte (the
// null terminator). `sizeof` counts that terminator; `strlen` from
// <string.h> counts only the characters before it.
//
// This program reports 6 characters for "hello". Fix it to print:
//
//     hello has 5 characters

#include <stdio.h>

int main(void)
{
    char greeting[] = "hello";

    printf("%s has %zu characters\n", greeting, sizeof(greeting));
    return 0;
}
