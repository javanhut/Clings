// macros2.c
//
// CONCEPT
// Two more ways macros bite:
//
// 1. A macro that expands to several statements breaks inside an
//    unbraced `if`:
//        #define SWAP(a, b) tmp = a; a = b; b = tmp
//        if (x > y) SWAP(x, y);      // only `tmp = a;` is conditional!
//    The fix is to wrap the body in `do { ... } while (0)`, which is a
//    single statement that still needs the trailing semicolon, so the
//    macro call reads like a function call everywhere.
//
// 2. Arguments are pasted, not evaluated, so an argument with a side
//    effect runs once per use in the body:
//        #define MAX(a, b) ((a) > (b) ? (a) : (b))
//        MAX(i++, 10)                 // i is incremented once or twice
//    Nothing in the macro can fix that; the rule is: never pass an
//    expression with side effects to a macro, and document macros that
//    evaluate arguments more than once. Or make it a function.
//
// WHEN YOU USE THIS
// Reading other people's macros (every code base has a SWAP, a MIN, a
// LOG). Writing your own: braces via do/while(0), parentheses
// everywhere, uppercase name so the reader knows it is a macro.
//
// TASK
// Fix SWAP with the do/while(0) idiom and fix the MAX call site so `i`
// is incremented exactly once. Do not change the `if` statements.
//
// EXPECTED OUTPUT
//     after swap: a = 5, b = 2
//     unchanged: c = 1, d = 9
//     max = 10, i = 4

#include <stdio.h>

#define SWAP(x, y) tmp = x; x = y; y = tmp
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void)
{
    int tmp;
    int a = 2;
    int b = 5;
    int c = 1;
    int d = 9;
    int i = 3;

    if (a < b)
        SWAP(a, b);
    if (c > d)
        SWAP(c, d);
    printf("after swap: a = %d, b = %d\n", a, b);
    printf("unchanged: c = %d, d = %d\n", c, d);

    int m = MAX(i++, 10);
    printf("max = %d, i = %d\n", m, i);
    return 0;
}
