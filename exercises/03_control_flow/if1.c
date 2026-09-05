// if1.c
//
// CONCEPT
// `=` assigns. `==` compares. Both are expressions with a value: `x = 5`
// assigns 5 to x *and* has the value 5, which is "true". So `if (x = 5)`
// compiles, sets x to 5, and always takes the true branch. The compiler
// warns ("suggest parentheses around assignment used as truth value")
// because it is nearly always a mistake, and Clings fails on warnings.
//
// Other truth rules: any non-zero value is true, 0 is false, a null pointer
// is false. `!x` is 1 when x is 0 and 0 otherwise. `&&` and `||`
// short-circuit: in `p != NULL && p->x > 0`, the right side is not
// evaluated when the left side is false, which is what makes that pattern
// safe.
//
// WHEN YOU USE THIS
// Every condition you write. Some people write `if (5 == x)` so that a
// typo becomes a compile error ("Yoda conditions"); the warning flag makes
// that unnecessary, but you will see it in old code.
//
// TASK
// Fix the comparison.
//
// EXPECTED OUTPUT
//     x is not five

#include <stdio.h>

int main(void)
{
    int x = 3;

    if (x = 5) {
        printf("x is five\n");
    } else {
        printf("x is not five\n");
    }
    return 0;
}
