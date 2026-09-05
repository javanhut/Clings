// variables1.c
//
// CONCEPT
// C is *statically typed*: every variable must be declared with a type
// before it is used, and it keeps that type forever. A declaration looks
// like `int x;` (type, then name). You can initialize at the same time:
// `int x = 42;`. The compiler uses the type to decide how many bytes the
// variable takes and what the operations on it mean.
//
// A variable that is declared but not initialized holds garbage: whatever
// bytes happened to be in that memory. Reading it is undefined behavior.
// Rule of thumb: always initialize at the point of declaration.
//
// WHEN YOU USE THIS
// Everywhere. The habit that matters most is declaring variables as close
// as possible to where they are used, with an initial value. Old C89 code
// piles all declarations at the top of a function; modern C does not need
// to, and it is clearer not to.
//
// TASK
// The program uses `x` without declaring it. Declare it (with the value 42)
// so the program prints the expected output.
//
// EXPECTED OUTPUT
//     x is 42

#include <stdio.h>

int main(void)
{
    x = 42;
    printf("x is %d\n", x);
    return 0;
}
