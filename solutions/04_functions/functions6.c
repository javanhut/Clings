// functions6.c - solution

#include <stdio.h>

static int counter = 0;

int next_id(void)
{
    counter++;
    return counter;
}

void reset_ids(void)
{
    counter = 0;
}

int main(void)
{
    int a = next_id();
    int b = next_id();
    int c = next_id();
    printf("ids: %d %d %d\n", a, b, c);
    reset_ids();
    int d = next_id();
    int e = next_id();
    printf("after reset: %d %d\n", d, e);
    return 0;
}
