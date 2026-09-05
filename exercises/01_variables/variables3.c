// variables3.c
//
// CONCEPT
// The basic types of C, roughly from small to large:
//
//     char      one byte; a character or a tiny integer
//     int       the "natural" integer, 32 bits on every platform you will meet
//     long      at least 32 bits, 64 on Linux/macOS, 32 on Windows (!)
//     long long at least 64 bits
//     float     32-bit floating point, about 7 significant digits
//     double    64-bit floating point, about 15 significant digits
//
// Storing a value in a type that cannot represent it silently loses
// information: `int price = 9.99;` keeps 9 and throws the rest away. The
// compiler does not complain unless you ask it to (-Wconversion).
//
// WHEN YOU USE THIS
// Use `int` for counting things and `double` for measurements. `float`
// exists for huge arrays where memory matters (graphics, audio); its
// precision is poor enough that `0.1f + 0.2f` is visibly wrong. Money is
// never a float: store cents in an integer.
//
// TASK
// Pick a type for `price` that keeps the fractional part.
//
// EXPECTED OUTPUT
//     Price: 9.99

#include <stdio.h>

int main(void)
{
    int price = 9.99;

    printf("Price: %.2f\n", price);
    return 0;
}
