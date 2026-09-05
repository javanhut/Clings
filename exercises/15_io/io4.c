// io4.c
//
// CONCEPT
// `scanf` parses formatted input, the mirror image of printf: `%d`
// reads an int, `%s` a whitespace-delimited word, `%lf` a double. It
// needs *addresses* to store into (`&n`), returns how many items it
// converted, and stops at the first mismatch, leaving the rest of the
// input unread. Its traps:
//
//   - forgetting `&`: passing an int where an int* is expected; the
//     compiler warns, the program writes to a random address,
//   - ignoring the return value: on bad input the variable is untouched
//     (garbage if uninitialized) and the loop spins forever on the same
//     unread characters,
//   - `%s` with no width: reads until whitespace, however long; a buffer
//     overflow waiting to happen. Write `%15s` for a char[16].
//
// The robust pattern is fgets a line, then sscanf the line (same format
// language, reads from a string): bad input costs you one line instead
// of a stuck stream.
//
// WHEN YOU USE THIS
// Quick parsing of well-formed input: numbers in a file you generated,
// "x y z" triples. Not for user input you do not control.
//
// TASK
// The program reads "name age" pairs from stdin until end of input and
// prints them. It has all three bugs. Fix them: read each line with
// fgets, parse it with sscanf using a width for the name, and skip a
// line that does not parse (printing "bad line: <text>"), so that the
// program terminates and prints the expected output.
//
// EXPECTED OUTPUT
//     Ada is 36
//     Grace is 45
//     bad line: oops
//     Linus is 54

#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[16];
    int age;

    while (scanf("%s %d", name, age) != EOF) {
        printf("%s is %d\n", name, age);
    }
    return 0;
}
