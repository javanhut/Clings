// pointers3.c
//
// An array's name behaves like a pointer to its first element, and adding
// an integer to a pointer moves it that many *elements* forward (not
// bytes). Replace `???` so that p points to the last element. Expected:
//
//     first: 5
//     last: 20

#include <stdio.h>

int main(void)
{
    int values[] = {5, 10, 15, 20};
    int *p = values;

    printf("first: %d\n", *p);

    p = p + ???;

    printf("last: %d\n", *p);
    return 0;
}
