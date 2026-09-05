// enums1.c
//
// CONCEPT
// An `enum` names a set of integer constants. Unless you say otherwise
// the first is 0, the next 1, and so on. You can assign explicit values
// (`RED = 1`), and later names continue from there. The type
// `enum color` is really just an int: nothing stops you from storing 42
// in it, and enum values from two different enums compare as plain
// numbers. What you get is readable names and, in a `switch` without a
// `default`, a compiler warning when a value is not handled
// (-Wswitch, part of -Wall).
//
// The standard companion is a function that turns a value into its
// name, because printing an enum with %d gives you the number.
//
// WHEN YOU USE THIS
// States, kinds, modes, error codes, opcodes, the tag of a tagged union.
// Anywhere you would otherwise write magic numbers or a set of #defines.
//
// TASK
// `color_name` is missing a case. Complete it.
//
// EXPECTED OUTPUT
//     GREEN has value 1
//     GREEN is called green

#include <stdio.h>

enum color {
    RED,
    GREEN,
    BLUE,
};

const char *color_name(enum color c)
{
    switch (c) {
    case RED:
        return "red";
    // TODO: handle GREEN
    case BLUE:
        return "blue";
    }
    return "unknown";
}

int main(void)
{
    enum color c = GREEN;

    printf("GREEN has value %d\n", c);
    printf("GREEN is called %s\n", color_name(c));
    return 0;
}
