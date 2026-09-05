// fnptr3.c - solution

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef int (*unary_fn)(int);
typedef bool (*predicate_fn)(int);
typedef int (*binary_fn)(int, int);

static int square(int x)
{
    return x * x;
}

static bool is_odd(int x)
{
    return x % 2 != 0;
}

static int add(int a, int b)
{
    return a + b;
}

static int max2(int a, int b)
{
    return a > b ? a : b;
}

void map(int *a, size_t n, unary_fn f)
{
    for (size_t i = 0; i < n; i++) {
        a[i] = f(a[i]);
    }
}

size_t count_if(const int *a, size_t n, predicate_fn p)
{
    size_t count = 0;

    for (size_t i = 0; i < n; i++) {
        if (p(a[i])) {
            count++;
        }
    }
    return count;
}

int reduce(const int *a, size_t n, int init, binary_fn f)
{
    int acc = init;

    for (size_t i = 0; i < n; i++) {
        acc = f(acc, a[i]);
    }
    return acc;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    size_t n = sizeof a / sizeof a[0];

    map(a, n, square);
    printf("squared:");
    for (size_t i = 0; i < n; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
    printf("odd count: %zu\n", count_if(a, n, is_odd));
    printf("sum: %d\n", reduce(a, n, 0, add));
    printf("max: %d\n", reduce(a, n, a[0], max2));
    return 0;
}
