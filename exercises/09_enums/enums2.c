// enums2.c
//
// CONCEPT
// Two idioms that make enums useful as array indices:
//
//   1. A final sentinel name gives the number of values for free:
//          enum direction { NORTH, EAST, SOUTH, WEST, DIRECTION_COUNT };
//      Add a value before it and the count updates itself.
//   2. A table indexed by the enum:
//          static const char *names[DIRECTION_COUNT] = {"north", ...};
//      With the count in the array size, the compiler complains if you
//      list too many names; sadly not if you list too few (missing ones
//      are NULL), so keep them in the same order and same file.
//
// Arithmetic on enums is ordinary int arithmetic: `(d + 1) %
// DIRECTION_COUNT` turns right, with the cast back to the enum type
// being implicit in C.
//
// WHEN YOU USE THIS
// Name tables for logging and error messages, per-kind dispatch tables,
// counters per category, iterating over all values of an enum.
//
// TASK
// Replace the `???`s: the sentinel, and a `turn_right` function that
// returns the next direction clockwise, wrapping from WEST to NORTH.
//
// EXPECTED OUTPUT
//     0: north
//     1: east
//     2: south
//     3: west
//     right of west is north

#include <stdio.h>

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    ???
};

static const char *names[DIRECTION_COUNT] = {
    "north",
    "east",
    "south",
    "west",
};

enum direction turn_right(enum direction d)
{
    return ???;
}

int main(void)
{
    for (int d = 0; d < DIRECTION_COUNT; d++) {
        printf("%d: %s\n", d, names[d]);
    }
    printf("right of west is %s\n", names[turn_right(WEST)]);
    return 0;
}
