// pointers4.c
//
// CONCEPT
// `NULL` is a pointer value that points to nothing. It is the universal
// "no result" / "not provided" / "end of list" marker. Dereferencing it
// crashes the program (a "segmentation fault", or a sanitizer report
// here). Any function that accepts a pointer must decide: is NULL a
// valid input? If yes, check for it first. If no, document that, and the
// caller must never pass it.
//
// Because 0 and NULL are false in conditions, `if (!p)` and `if (p)` are
// idiomatic tests. Prefer `if (p == NULL)` while learning.
//
// WHEN YOU USE THIS
// malloc returns NULL when memory runs out; fopen returns NULL when the
// file cannot be opened; strchr returns NULL when the character is not
// found; a linked list ends when `next` is NULL. Checking for NULL where
// it can occur is not optional in C.
//
// TASK
// Make `print_length` print "(null)" when it receives NULL.
//
// EXPECTED OUTPUT
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
