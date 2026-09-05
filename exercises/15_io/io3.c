// io3.c
//
// CONCEPT
// Reading text a line at a time:
//
//     char line[256];
//     while (fgets(line, sizeof line, stdin) != NULL) {
//         ... line includes the '\n' if the line fit ...
//     }
//
// fgets reads up to size-1 characters or through the newline, always
// terminates the string, and returns NULL at end of input (or error).
// The newline stays in the buffer; strip it with
// `line[strcspn(line, "\n")] = '\0';` (strcspn finds the first
// character from the set). If a line is longer than the buffer, fgets
// returns the first chunk and the next call returns the rest, so a
// "line" without a trailing '\n' is either the last line of the input
// or a partial one.
//
// Never use gets (removed from C11: no size, guaranteed overflow) and
// prefer fgets + parsing over scanf for anything a human typed.
//
// End of input on a terminal is Ctrl-D (Unix) or Ctrl-Z Enter
// (Windows); from a pipe or file it is simply the end of the data.
//
// WHEN YOU USE THIS
// Filters in the Unix tradition: read stdin, transform, write stdout.
// Log processing, config parsing, interactive prompts. This is the
// bread and butter of C tooling.
//
// TASK
// Clings feeds this program a few lines on stdin. Write a small `wc`:
// count lines, words (runs of non-whitespace) and characters (including
// newlines), and print the longest line's length and text (strip its
// newline). Lines are at most 200 characters.
//
// EXPECTED OUTPUT
//     lines: 4
//     words: 9
//     chars: 48
//     longest (22): the quick brown fox...

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // TODO
    return 0;
}
