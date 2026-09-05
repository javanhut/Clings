// io1.c
//
// CONCEPT
// A program receives its command line through main's parameters:
//
//     int main(int argc, char *argv[])
//
// `argc` is the number of arguments including the program name; `argv`
// is an array of strings: argv[0] is the program name (or path, which
// varies, so never rely on its exact text), argv[1] .. argv[argc-1] are
// the arguments, and argv[argc] is NULL. Every argument is a *string*,
// even "42"; converting is your job (strings8).
//
// The shell splits the command line on spaces and removes quotes before
// the program sees it, so `prog "hello world" 3` gives argc == 3 with
// argv[1] == "hello world".
//
// WHEN YOU USE THIS
// Every command-line tool. The C convention is: options like `-v` or
// `--output file` first, then positional arguments; getopt (POSIX) and
// getopt_long (GNU) parse the option part for you. Here we do it by
// hand to see the shape.
//
// TASK
// Clings runs this program with the arguments: -v alpha beta gamma.
// Print how many arguments there are (not counting the program name),
// then each one with its index, then treat a leading "-v" as a verbose
// flag: print "verbose: on" if argv[1] is "-v" (and skip it in the
// positional list), otherwise "verbose: off". The positional arguments
// follow, one per line.
//
// EXPECTED OUTPUT
//     4 arguments
//     [1] -v
//     [2] alpha
//     [3] beta
//     [4] gamma
//     verbose: on
//     positional: alpha
//     positional: beta
//     positional: gamma

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // TODO
    (void)argc;
    (void)argv;
    return 0;
}
