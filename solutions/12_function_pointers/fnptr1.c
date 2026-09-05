// fnptr1.c - solution

#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int mul(int a, int b)
{
    return a * b;
}

typedef int (*binary_op)(int, int);

binary_op pick(char symbol)
{
    return symbol == '*' ? mul : add;
}

int main(void)
{
    int (*op)(int, int);

    op = add;
    printf("2 + 3 = %d\n", op(2, 3));
    op = mul;
    printf("2 * 3 = %d\n", op(2, 3));
    printf("picked: %d\n", pick('+')(2, 3));
    return 0;
}
