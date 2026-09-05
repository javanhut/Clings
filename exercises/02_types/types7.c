// types7.c
//
// CONCEPT
// A double stores a number as a binary fraction with 53 bits of precision.
// Most decimal fractions cannot be represented exactly: 0.1 is really
// 0.1000000000000000055511151231257827... Every operation rounds to the
// nearest representable value, and rounding errors accumulate. Adding 0.1
// ten times does not give 1.0.
//
// Consequences:
//   - never compare floating-point values with `==`; compare the
//     difference against a small tolerance (an "epsilon"),
//   - print with a precision that matches what you know: %.2f for money
//     you should not have stored as a double in the first place, %.17g
//     when you need the exact stored value round-tripped,
//   - integers up to 2^53 are exact in a double; beyond that, they are not.
//
// WHEN YOU USE THIS
// Physics, statistics, graphics, anything measured. And when a test that
// compares floats "randomly" fails on another machine. `fabs` from
// <math.h> gives the absolute value of a double.
//
// TASK
// Write `nearly_equal`, which returns true when a and b differ by less
// than `epsilon`, and complete main: add 0.1 to `sum` ten times in a loop,
// then print the lines below. %.17g shows the value with enough digits to
// see the error.
//
// EXPECTED OUTPUT
//     sum = 0.99999999999999989
//     sum == 1.0: no
//     nearly_equal(sum, 1.0): yes

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool nearly_equal(double a, double b, double epsilon)
{
    // TODO
    (void)a;
    (void)b;
    (void)epsilon;
    return false;
}

int main(void)
{
    double sum = 0.0;

    // TODO: add 0.1 ten times.

    printf("sum = %.17g\n", sum);
    printf("sum == 1.0: %s\n", sum == 1.0 ? "yes" : "no");
    printf("nearly_equal(sum, 1.0): %s\n",
           nearly_equal(sum, 1.0, 1e-9) ? "yes" : "no");
    return 0;
}
