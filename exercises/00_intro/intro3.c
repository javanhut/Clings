// intro3.c
//
// CONCEPT
// `printf` takes a *format string* followed by the values to print. Inside
// the format string, a `%` sequence is a placeholder that says "put the
// next argument here, formatted like this":
//
//     %d    an int                         printf("%d", 42)      -> 42
//     %f    a double, 6 decimals           printf("%f", 1.5)     -> 1.500000
//     %.2f  a double, 2 decimals           printf("%.2f", 1.5)   -> 1.50
//     %c    a single character             printf("%c", 'A')     -> A
//     %s    a string                       printf("%s", "hi")    -> hi
//     %zu   a size_t (sizes and lengths)   printf("%zu", sizeof(int)) -> 4
//     %%    a literal percent sign
//
// The placeholders are matched to the arguments left to right, and the
// types must agree: printing an int with %f is undefined behavior (the
// compiler warns you, and Clings treats warnings as failures).
//
// WHEN YOU USE THIS
// printf is how C programs report anything: log lines, tables, error
// messages. The same format language is used by snprintf (formatting into a
// string), fprintf (formatting into a file) and by many other languages that
// copied it. Knowing it cold pays off daily.
//
// TASK
// This is the first "Write" exercise: the variables are given and there is
// no bug to find. Write the printf calls that produce the expected output.
// Use every variable; Clings fails on unused-variable warnings.
//
// EXPECTED OUTPUT
//     Name: Ada
//     Age: 36
//     Height: 1.70 m
//     Initial: A
//     Progress: 100%

#include <stdio.h>

int main(void)
{
    const char *name = "Ada";
    int age = 36;
    double height = 1.7;
    char initial = 'A';

    // TODO: print the five lines shown above.

    return 0;
}
