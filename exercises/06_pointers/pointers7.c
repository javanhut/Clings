// pointers7.c
//
// CONCEPT
// `const` and pointers combine in two independent ways. Read declarations
// from right to left:
//
//     const int *p;        // p is a pointer to a const int:
//                          //   *p cannot be assigned, p can be repointed
//     int *const p;        // p is a const pointer to int:
//                          //   p cannot be repointed, *p can be assigned
//     const int *const p;  // neither
//
// The first form is the important one. A function taking `const char *s`
// promises not to modify the string, so callers can safely pass string
// literals and shared data. Converting `T *` to `const T *` is free and
// implicit; the other direction needs a cast and is a red flag.
//
// "const correctness" means every pointer parameter that is only read is
// declared const. The compiler then enforces the promise inside the
// function and warns when a const pointer is passed where a non-const
// one is expected ("discards const qualifier").
//
// WHEN YOU USE THIS
// Every function signature you write. It is documentation the compiler
// checks: seeing `const` in a prototype tells the reader that argument
// comes back unchanged.
//
// TASK
// This file has three const problems: one function modifies through a
// const pointer (it must not; fix the function, not the const), one
// function is missing a const it should have (so the call with a literal
// warns), and one const pointer is repointed. Make it compile clean.
//
// EXPECTED OUTPUT
//     shout: HELLO
//     length: 5
//     total: 6

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prints the string in upper case without modifying it.
void shout(const char *s)
{
    for (size_t i = 0; s[i] != '\0'; i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
    printf("shout: %s\n", s);
}

size_t length(char *s)
{
    return strlen(s);
}

int main(void)
{
    const char *word = "hello";
    int a = 1;
    int b = 5;
    int *const fixed = &a;

    shout(word);
    printf("length: %zu\n", length("hello"));
    fixed = &b;
    *fixed += 5;
    printf("total: %d\n", *fixed);
    return 0;
}
