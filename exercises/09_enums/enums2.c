// enums2.c
//
// A common trick: put an extra name at the end of an enum to get the
// number of values, and use the enum values as indices into an array of
// names. Replace `???` with that extra name. Expected output:
//
//     0: north
//     1: east
//     2: south
//     3: west

#include <stdio.h>

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    DIRECTION_COUNT,
};

const char *names[DIRECTION_COUNT] = {"north", "east", "south", "west"};

int main(void)
{
    for (int d = 0; d < ???; d++) {
        printf("%d: %s\n", d, names[d]);
    }
    return 0;
}
