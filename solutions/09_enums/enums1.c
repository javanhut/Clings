// enums1.c
//
// An enum gives names to a set of integer constants. Unless you say
// otherwise, the first name is 0, the next is 1, and so on. Enums pair
// naturally with `switch`.
//
// `color_name` is missing a case. Complete it so the program prints:
//
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
    case GREEN:
        return "green";
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
