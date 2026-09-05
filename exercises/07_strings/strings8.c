// strings8.c
//
// CONCEPT
// Turning text into numbers: `atoi("42")` is simple and useless for real
// input, because it returns 0 both for "0" and for "hello", and says
// nothing about overflow. The proper tool is strtol:
//
//     char *end;
//     errno = 0;
//     long v = strtol(text, &end, 10);
//     if (end == text)      -> no digits at all
//     if (*end != '\0')     -> trailing junk after the number ("12abc")
//     if (errno == ERANGE)  -> value out of range for long
//
// `end` is an output parameter (pointers5!) that receives a pointer to
// the first character strtol did not consume. Base 10 here; base 16
// parses "ff", base 0 auto-detects "0x" and "0" prefixes.
//
// Splitting text on a delimiter: `strtok(s, ",")` returns the first
// token and replaces the delimiter with '\0' *in your buffer*;
// `strtok(NULL, ",")` returns the next one, and NULL at the end. It
// modifies the string, keeps hidden state between calls, and merges
// adjacent delimiters; it is fine for quick jobs and wrong for anything
// concurrent or that needs empty fields. strtok_r / strtok_s are the
// re-entrant versions.
//
// WHEN YOU USE THIS
// Command-line arguments, config files, CSV, any text protocol. Parsing
// with error reporting is what separates a script from a tool.
//
// TASK
// Write `parse_int`, which returns true and stores the value only when
// the whole string is a valid int (also reject values outside INT_MIN..
// INT_MAX). Then write `sum_csv`, which splits `line` on commas with
// strtok, sums the valid numbers, prints "bad token: X" for every token
// that is not a number, and returns the sum. sum_csv may modify `line`.
//
// EXPECTED OUTPUT
//     parse "42" -> ok 42
//     parse "-7" -> ok -7
//     parse "12abc" -> error
//     parse "" -> error
//     parse "99999999999" -> error
//     bad token: x
//     bad token: 4.5
//     sum = 60

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_int(const char *text, int *out)
{
    // TODO
    (void)text;
    (void)out;
    return false;
}

int sum_csv(char *line)
{
    // TODO
    (void)line;
    return 0;
}

static void try_parse(const char *text)
{
    int v;
    if (parse_int(text, &v)) {
        printf("parse \"%s\" -> ok %d\n", text, v);
    } else {
        printf("parse \"%s\" -> error\n", text);
    }
}

int main(void)
{
    char line[] = "10,20,x,30,4.5";

    try_parse("42");
    try_parse("-7");
    try_parse("12abc");
    try_parse("");
    try_parse("99999999999");
    printf("sum = %d\n", sum_csv(line));
    return 0;
}
