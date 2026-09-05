// types6.c - solution

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int32_t a = INT32_MAX;
    int32_t b = INT32_MAX;
    int64_t sum = (int64_t)a + b;

    printf("int32_t is %zu bytes, int64_t is %zu bytes\n", sizeof(int32_t),
           sizeof(int64_t));
    printf("INT32_MAX = %" PRId32 "\n", INT32_MAX);
    printf("sum as int64_t = %" PRId64 "\n", sum);
    return 0;
}
