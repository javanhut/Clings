// ub3.c - solution

#include <limits.h>
#include <stdio.h>

int safe_div(int a, int b)
{
    if (b == 0 || (a == INT_MIN && b == -1)) {
        return 0;
    }
    return a / b;
}

int main(void)
{
    int i = 3;
    int a[3] = {0};

    i = i + 1;
    printf("i = %d\n", i);

    int k = 0;
    while (k < 3) {
        a[k] = k;
        k++;
    }
    printf("a = %d %d %d\n", a[0], a[1], a[2]);

    printf("7 / 2 = %d\n", safe_div(7, 2));
    printf("-7 / 2 = %d\n", safe_div(-7, 2));
    printf("1 / 0 = %d\n", safe_div(1, 0));
    printf("INT_MIN / -1 = %d\n", safe_div(INT_MIN, -1));
    return 0;
}
