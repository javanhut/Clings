// enums1.c - solution

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
