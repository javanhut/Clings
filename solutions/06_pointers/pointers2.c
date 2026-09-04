// pointers2.c
//
// Remember functions3: arguments are copied, so `swap` below swaps its own
// copies and main never notices. Pointers are the way out: pass the
// *addresses* of a and b, and swap the values they point to.
//
// Change `swap` to take pointers and update the call in main. Expected:
//
//     a = 2, b = 1

#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int a = 1;
    int b = 2;

    swap(&a, &b);

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
