// ub2.c
//
// CONCEPT
// Signed integer overflow is undefined. `INT_MAX + 1` does not "wrap to
// INT_MIN" as far as the language is concerned, even though the CPU
// would do that. The compiler assumes it cannot happen: it will happily
// turn `if (x + 1 < x)` into `if (0)`, deleting your overflow check.
// UndefinedBehaviorSanitizer reports "signed integer overflow" the
// moment it occurs.
//
// The safe ways:
//   - use a wider type (long long, int64_t) when the range allows,
//   - check *before* the operation: `if (a > INT_MAX - b)` for
//     addition, `if (a != 0 && b > LLONG_MAX / a)` for multiplication,
//   - use unsigned types where wrapping is what you want (hashes),
//     because unsigned overflow *is* defined to wrap,
//   - gcc and clang offer `__builtin_add_overflow(a, b, &result)` and
//     friends, which are exact and fast; C23 standardizes them in
//     <stdckdint.h> as ckd_add / ckd_mul.
//
// WHEN YOU USE THIS
// Size computations (`rows * cols * sizeof(T)` is the classic
// exploitable overflow), counters that run for a long time, arithmetic
// on untrusted input.
//
// TASK
// `factorial` overflows at 13!. Change it to compute in `unsigned long
// long` and to detect overflow *before* multiplying, returning 0 to
// mean "does not fit". main prints the first value that does not fit.
//
// EXPECTED OUTPUT
//     12! = 479001600
//     20! = 2432902008176640000
//     21! does not fit

#include <limits.h>
#include <stdio.h>

int factorial(int n)
{
    int result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void)
{
    printf("12! = %d\n", factorial(12));
    printf("20! = %d\n", factorial(20));
    for (int n = 13; n <= 25; n++) {
        if (factorial(n) == 0) {
            printf("%d! does not fit\n", n);
            break;
        }
    }
    return 0;
}
