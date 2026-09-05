// functions7.c - solution

#include <stdio.h>

void print_banner(const char *title)
{
    printf("=== %s ===\n", title);
}

double average(int a, int b)
{
    return (a + b) / 2.0;
}

int min(int a, int b, int unused_flag)
{
    (void)unused_flag;
    return a < b ? a : b;
}

int main(void)
{
    print_banner("Report");
    printf("average of 3 and 4 is %.1f\n", average(3, 4));
    printf("min of 3 and 4 is %d\n", min(3, 4, 0));
    return 0;
}
