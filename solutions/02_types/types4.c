// types4.c - solution

#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool ready = true;
    bool big = 42;

    if (ready) {
        printf("Ready!\n");
    }
    printf("42 stored in a bool is %d\n", big);
    return 0;
}
