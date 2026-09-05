// enums2.c - solution

#include <stdio.h>

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    DIRECTION_COUNT
};

static const char *names[DIRECTION_COUNT] = {
    "north",
    "east",
    "south",
    "west",
};

enum direction turn_right(enum direction d)
{
    return (d + 1) % DIRECTION_COUNT;
}

int main(void)
{
    for (int d = 0; d < DIRECTION_COUNT; d++) {
        printf("%d: %s\n", d, names[d]);
    }
    printf("right of west is %s\n", names[turn_right(WEST)]);
    return 0;
}
