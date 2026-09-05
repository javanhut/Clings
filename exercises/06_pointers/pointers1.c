// pointers1.c
//
// CONCEPT
// Every variable lives at an address in memory. A *pointer* is a variable
// that holds an address. Three pieces of syntax:
//
//     int *p;      // declare p as "pointer to int"
//     p = &x;      // & takes the address of x; p now points to x
//     *p = 20;     // * follows the pointer: assign to whatever p points to
//     int y = *p;  // ... or read it
//
// The `*` in the declaration and the `*` in `*p = 20` are different
// things: the first is part of the type, the second is the dereference
// operator. Reading `int *p` as "*p is an int" helps.
//
// The type of a pointer matters: `int *` knows it points at 4-byte ints,
// which makes `*p` read 4 bytes and (later) `p + 1` move 4 bytes. A pointer
// is typically 8 bytes on a 64-bit machine, whatever it points to.
//
// WHEN YOU USE THIS
// Pointers are how C does everything that other languages do with
// references: letting a function modify the caller's variable, sharing
// large data without copying, building linked structures, walking
// arrays, dynamic memory. Every later section builds on this one.
//
// TASK
// `p` is initialized with the *value* of x instead of its address, which
// the compiler rejects (an int is not a pointer). Fix the initialization.
//
// EXPECTED OUTPUT
//     x is 20
//     p points to a value of 20

#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p = x;

    *p = 20;
    printf("x is %d\n", x);
    printf("p points to a value of %d\n", *p);
    return 0;
}
