// types1.c
//
// CONCEPT
// The type of an expression is decided from the types of its operands,
// *before* the result is stored anywhere. `7 / 2` is int divided by int, so
// it is integer division and yields 3. Storing that 3 into a double gives
// 3.0; the .5 was never computed.
//
// A *cast* converts a value to another type: `(double)a` is the value of
// `a` as a double. If either operand of `/` is floating point, the whole
// division happens in floating point. So `(double)a / b` is 3.5, but
// `(double)(a / b)` is still 3.0 because the division already happened.
//
// WHEN YOU USE THIS
// Averages, ratios, percentages, unit conversions: anywhere two integers
// meet a `/`. This bug ships in real software constantly, because the code
// looks right and the compiler has nothing to say about it.
//
// TASK
// Make the division produce 3.5.
//
// EXPECTED OUTPUT
//     7 / 2 = 3.5

#include <stdio.h>

int main(void)
{
    int a = 7;
    int b = 2;
    double result = a / b;

    printf("%d / %d = %.1f\n", a, b, result);
    return 0;
}
