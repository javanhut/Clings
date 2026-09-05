// memory3.c
//
// CONCEPT
// A function cannot return a pointer to its own local array: the array
// is on the stack and is gone the moment the function returns. The
// compiler warns ("function returns address of local variable"), and
// what the caller reads is whatever the stack holds by then.
//
// Three correct ways to get a string out of a function:
//   1. allocate it on the heap with malloc and return it; the caller
//      owns it and must free it (document that!),
//   2. let the caller pass a buffer and its size (snprintf style),
//   3. return a pointer to a string literal or static storage, when the
//      text is fixed.
//
// WHEN YOU USE THIS
// Option 1 is how strdup, getline and asprintf work. Option 2 is what
// most of the standard library does. Read every function that returns a
// pointer with the question "who owns this, and how long does it live?"
//
// TASK
// Fix `make_greeting` using option 1: compute the needed size
// (strlen + strlen + the literal parts + 1 for the terminator), malloc
// it, snprintf into it, and free it in main.
//
// EXPECTED OUTPUT
//     Greeting: hello, Ada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_greeting(const char *name)
{
    char buffer[64];

    snprintf(buffer, sizeof(buffer), "hello, %s", name);
    return buffer;
}

int main(void)
{
    char *greeting = make_greeting("Ada");

    printf("Greeting: %s\n", greeting);
    return 0;
}
