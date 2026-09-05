// ternary1.c - solution

#include <stdio.h>

int max3(int a, int b, int c)
{
    int ab = a > b ? a : b;
    return ab > c ? ab : c;
}

const char *plural(int n)
{
    return n == 1 ? "" : "s";
}

int process(int fail_at)
{
    int result = -1;

    if (fail_at == 1) {
        printf("step 1 failed\n");
        goto cleanup;
    }
    printf("step 1 ok\n");
    if (fail_at == 2) {
        printf("step 2 failed\n");
        goto cleanup;
    }
    printf("step 2 ok\n");
    if (fail_at == 3) {
        printf("step 3 failed\n");
        goto cleanup;
    }
    printf("step 3 ok\n");
    result = 0;

cleanup:
    printf("cleanup done\n");
    return result;
}

int main(void)
{
    printf("max3(3, 9, 5) = %d\n", max3(3, 9, 5));
    printf("max3(-1, -7, -3) = %d\n", max3(-1, -7, -3));
    printf("1 item%s, 2 item%s, 0 item%s\n", plural(1), plural(2), plural(0));
    printf("process(2) returned %d\n", process(2));
    printf("process(4) returned %d\n", process(4));
    return 0;
}
