// intro1.c
//
// CONCEPT
// A C program is text that the *compiler* turns into a program the machine
// can run. Before it does anything else, the compiler checks that the text
// follows the grammar of C. If it does not, you get a compile error and no
// program at all.
//
// Every statement in C ends with a semicolon. Forgetting one is the most
// common first mistake, and the compiler's message tells you exactly where
// it noticed: `intro1.c:24:30: error: expected ';' ...` means file intro1.c,
// line 24, column 30. Learn to read that "file:line:column" prefix; you will
// see it thousands of times.
//
// WHEN YOU USE THIS
// Always. Compile errors are not failures, they are the compiler doing part
// of your testing for free. Clings compiles with -Wall -Wextra, which turns
// on extra warnings, and treats warnings as failures. Real projects do the
// same, because a warning is almost always a bug you have not hit yet.
//
// TASK
// Fix the compile error so the program prints the expected output.
//
// EXPECTED OUTPUT
//     Hello, Clings!

#include <stdio.h>

int main(void)
{
    printf("Hello, Clings!\n")
    return 0;
}
