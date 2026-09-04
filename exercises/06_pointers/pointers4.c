// pointers4.c
//
// NULL is a pointer that points to nothing. Dereferencing it (or passing it
// to a function like strlen that dereferences it) crashes the program.
// Functions that accept pointers should check for NULL when it is a valid
// input.
//
// Make `print_length` print "(null)" when it receives NULL. Expected:
//
//     hello has length 5
//     (null)

#include <stdio.h>
#include <string.h>

void print_length(const char *s)
{
    printf("%s has length %zu\n", s, strlen(s));
}

int main(void)
{
    print_length("hello");
    print_length(NULL);
    return 0;
}
