// ub3.c
//
// CONCEPT
// C does not specify the order in which the parts of most expressions
// are evaluated, and modifying a variable twice without a *sequence
// point* in between is undefined. Sequence points are the end of a
// full statement, the `&&`, `||`, `?:` and comma operators, and the
// entry to a function call. So:
//
//     i = i++ + 1;          // UB: i modified twice
//     a[i] = i++;           // UB: is i read before or after the ++?
//     f(i++, i);            // UB: same
//     printf("%d %d", g(), h());  // not UB, but g/h may run in any order
//
// -Wall's -Wsequence-point catches the simple shapes. The fix is
// always the same: one modification per statement, in the order you
// mean.
//
// A cousin: the result of `x / y` and `x % y` with a negative operand is
// defined (truncation toward zero, so -7 / 2 == -3 and -7 % 2 == -1),
// but `INT_MIN / -1` and any division by zero are undefined; the
// sanitizer catches both.
//
// WHEN YOU USE THIS
// Any time you are tempted to be clever with ++ inside a larger
// expression. `*dst++ = *src++` is the one idiom in this family that
// is well-defined and worth knowing; everything denser is a bug.
//
// TASK
// Fix the three undefined expressions so the program compiles without
// warnings and prints the expected output, keeping the obvious intended
// meaning (i ends up incremented once, the array gets 0 1 2 at indices
// 0 1 2, and `safe_div` returns 0 for the two undefined cases).
//
// EXPECTED OUTPUT
//     i = 4
//     a = 0 1 2
//     7 / 2 = 3
//     -7 / 2 = -3
//     1 / 0 = 0
//     INT_MIN / -1 = 0

#include <limits.h>
#include <stdio.h>

int safe_div(int a, int b)
{
    return a / b;
}

int main(void)
{
    int i = 3;
    int a[3] = {0};

    i = i++ + 1;
    printf("i = %d\n", i);

    int k = 0;
    while (k < 3) {
        a[k] = k++;
    }
    printf("a = %d %d %d\n", a[0], a[1], a[2]);

    printf("7 / 2 = %d\n", safe_div(7, 2));
    printf("-7 / 2 = %d\n", safe_div(-7, 2));
    printf("1 / 0 = %d\n", safe_div(1, 0));
    printf("INT_MIN / -1 = %d\n", safe_div(INT_MIN, -1));
    return 0;
}
