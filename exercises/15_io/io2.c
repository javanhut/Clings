// io2.c
//
// CONCEPT
// A program talks to the outside world through three channels and one
// number:
//   stdout     normal output; what the user asked for. Pipes and
//              redirection capture this.
//   stderr     diagnostics: errors, warnings, progress. Goes to the
//              terminal even when stdout is redirected to a file. Write
//              with fprintf(stderr, ...).
//   stdin      input (next exercise).
//   exit code  0 means success; anything else means failure. Scripts
//              and build systems check it (`prog && next`, `set -e`).
//              main's return value is the exit code; `exit(n)` from
//              anywhere does the same. <stdlib.h> gives EXIT_SUCCESS and
//              EXIT_FAILURE; specific tools define their own codes
//              (grep: 1 = no match, 2 = error).
//
// The rule: never print an error to stdout, never exit 0 on failure.
// A tool that prints "error: ..." to stdout and exits 0 breaks every
// script that uses it.
//
// WHEN YOU USE THIS
// Every program. Clings itself checks both your stdout and your exit
// code, and shows stderr separately.
//
// TASK
// Clings runs this program with the arguments: 7 6 x 5. Parse each
// argument as an int (write a small strtol-based checker like strings8,
// or reuse the idea). Sum the valid ones. For every invalid argument
// print "invalid number: <arg>" to *stderr*. At the end print the sum to
// stdout, and exit with the number of invalid arguments as the exit
// code (so 1 here), or 0 if all were valid.
//
// EXPECTED OUTPUT
//     sum of valid arguments: 18

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // TODO
    (void)argc;
    (void)argv;
    return 0;
}
