// fnptr1.c
//
// CONCEPT
// A function has an address too, and a variable can hold it. The
// declaration syntax is the ugliest in C, so learn it once:
//
//     int (*op)(int, int);       // op: pointer to function (int,int) -> int
//     op = add;                  // a function name is its address
//     int r = op(2, 3);          // call through the pointer
//
// The parentheses around `*op` are required: `int *op(int, int)` declares
// a *function* named op that returns `int *`. A typedef hides the mess:
//
//     typedef int (*binary_op)(int, int);
//     binary_op op = add;
//
// `&add` and `add` mean the same thing, as do `(*op)(2, 3)` and
// `op(2, 3)`; you will see both styles.
//
// WHEN YOU USE THIS
// Function pointers are C's mechanism for "pass behavior as data":
// sorting with a custom comparison, event callbacks, plugin tables,
// virtual-method tables in object-oriented C, state machines where each
// state is a function. Every non-trivial C library API has some.
//
// TASK
// The declaration of `op` is wrong (it declares a function, not a
// pointer). Fix it, and add the typedef `binary_op` so that `pick`
// compiles.
//
// EXPECTED OUTPUT
//     2 + 3 = 5
//     2 * 3 = 6
//     picked: 5

#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int mul(int a, int b)
{
    return a * b;
}

// TODO: typedef binary_op

binary_op pick(char symbol)
{
    return symbol == '*' ? mul : add;
}

int main(void)
{
    int *op(int, int);

    op = add;
    printf("2 + 3 = %d\n", op(2, 3));
    op = mul;
    printf("2 * 3 = %d\n", op(2, 3));
    printf("picked: %d\n", pick('+')(2, 3));
    return 0;
}
