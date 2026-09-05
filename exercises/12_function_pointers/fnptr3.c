// fnptr3.c
//
// CONCEPT
// A function that takes a function is a *higher-order function*. C has
// no lambdas, so the "small function" must be written out with a name,
// but the shapes are the same as map/filter/reduce elsewhere:
//
//     void map(int *a, size_t n, int (*f)(int));           // a[i] = f(a[i])
//     size_t count_if(const int *a, size_t n, bool (*p)(int));
//     int reduce(const int *a, size_t n, int init, int (*f)(int, int));
//
// Using typedefs for the function-pointer parameter types keeps the
// signatures readable. Passing `square` where an `int (*)(int)` is
// expected needs no cast; the compiler checks the signature matches.
//
// WHEN YOU USE THIS
// Generic array utilities, visitors over trees and lists, "apply this to
// every entry". It is also how you write code that is testable in
// isolation: the algorithm takes the policy as a parameter.
//
// TASK
// Write map, count_if and reduce, and the small functions square,
// is_odd, add and max2 used by main.
//
// EXPECTED OUTPUT
//     squared: 1 4 9 16 25
//     odd count: 3
//     sum: 55
//     max: 25

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef int (*unary_fn)(int);
typedef bool (*predicate_fn)(int);
typedef int (*binary_fn)(int, int);

// TODO: square, is_odd, add, max2

void map(int *a, size_t n, unary_fn f)
{
    // TODO
    (void)a;
    (void)n;
    (void)f;
}

size_t count_if(const int *a, size_t n, predicate_fn p)
{
    // TODO
    (void)a;
    (void)n;
    (void)p;
    return 0;
}

int reduce(const int *a, size_t n, int init, binary_fn f)
{
    // TODO: acc = f(acc, a[i]) for each element, starting from init.
    (void)a;
    (void)n;
    (void)f;
    return init;
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
