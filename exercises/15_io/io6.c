// io6.c
//
// CONCEPT
// When a library call fails it usually returns a sentinel (NULL, -1,
// EOF) and sets the global `errno` (from <errno.h>) to a code saying
// why: ENOENT (no such file), EACCES (permission denied), ENOMEM, ...
// `strerror(errno)` turns the code into text; `perror("prefix")` prints
// "prefix: <that text>" to stderr. errno is only meaningful right after
// a failed call; a later call may overwrite it, so save it first if you
// need it later.
//
// A C program's error handling is therefore a discipline, not a
// feature:
//   - check every call that can fail (fopen, malloc, fgets, strtol...),
//   - report to stderr with enough context (which file? which line?),
//   - clean up what was already acquired (memory5's goto pattern),
//   - return an error to the caller, or exit with a non-zero code from
//     main. Library code returns; only main (or a tool's top level)
//     exits.
//
// WHEN YOU USE THIS
// Everywhere. The difference between a program that says "config.txt:
// No such file or directory" and one that segfaults is this section.
//
// TASK
// Write `count_lines`, which opens `path`, counts its lines and stores
// the count in `*out`, returning 0 on success or -1 on failure; on
// failure it prints "<path>: <strerror text>" to stderr and does not
// touch `*out`. Then complete main: it is given a path that does not
// exist, must print "counting lines in <path>" first, and must exit
// with EXIT_FAILURE when count_lines fails (and print the count and
// exit 0 when it succeeds).
//
// EXPECTED OUTPUT
//     counting lines in /nonexistent/clings/input.txt

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(const char *path, long *out)
{
    // TODO
    (void)path;
    (void)out;
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s FILE\n", argv[0]);
        return EXIT_FAILURE;
    }
    // TODO
    return 0;
}
