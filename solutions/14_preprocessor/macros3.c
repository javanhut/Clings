// macros3.c - solution

#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))
#define SHOW(expr) printf(#expr " = %d\n", (expr))
#define CHECK(cond)                             \
    do {                                        \
        if (cond) {                             \
            printf("ok: " #cond "\n");          \
        } else {                                \
            printf("FAIL: " #cond "\n");        \
        }                                       \
    } while (0)

int main(void)
{
    int values[] = {10, 20, 30, 40};
    int a = 3;
    int b = 4;

    printf("values has %zu elements\n", ARRAY_LEN(values));
    SHOW(a + b);
    SHOW(values[2] * 2);
    CHECK(a < b);
    CHECK(a == b);
    CHECK(ARRAY_LEN(values) == 4);
    return 0;
}
