// functions1.c
//
// CONCEPT
// The compiler reads a file top to bottom and must know a function's
// *signature* (return type and parameter types) before it sees a call.
// Otherwise it cannot check the arguments or know what the call returns.
// Old C guessed `int`; modern C makes it an error.
//
// There are two ways to tell it:
//   - define the function above its first use, or
//   - put a *prototype* (declaration) above: `void greet(void);` says "a
//     function named greet exists, takes nothing, returns nothing; the body
//     is elsewhere". The body can then come later, or even from another
//     file.
// `(void)` means "no parameters". A bare `()` in a declaration means
// "unspecified parameters" before C23, which disables argument checking.
// Always write `(void)`.
//
// WHEN YOU USE THIS
// Every header file (.h) is a list of prototypes: it tells users of a
// library what functions exist without shipping the bodies. Inside one
// file, prototypes let you order functions for reading (main first, then
// helpers) and let two functions call each other.
//
// TASK
// Make the program compile without moving `greet` below main... or rather,
// keep it where it is and add what the compiler needs.
//
// EXPECTED OUTPUT
//     Hello from a function!

#include <stdio.h>

int main(void)
{
    greet();
    return 0;
}

void greet(void)
{
    printf("Hello from a function!\n");
}
