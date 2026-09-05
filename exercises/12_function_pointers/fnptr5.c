// fnptr5.c
//
// CONCEPT
// A callback often needs some state: "add every value to *this* total",
// "write into *this* buffer". C functions cannot capture variables like
// closures do, so the convention is an extra `void *ctx` parameter that
// the library passes through untouched:
//
//     typedef void (*visit_fn)(int value, void *ctx);
//     void for_each(const int *a, size_t n, visit_fn f, void *ctx);
//
// The caller points ctx at whatever struct it likes, and the callback
// casts it back. That is a closure, assembled by hand: function pointer
// plus data pointer. Almost every C API with callbacks has this shape
// (pthread_create, qsort_r, signal handlers via sigaction's siginfo, GUI
// toolkits, libcurl's write callback).
//
// WHEN YOU USE THIS
// Whenever a callback needs to accumulate, count, log to a particular
// stream, or update a particular object. If you find yourself reaching
// for a global variable to get data into a callback, this is what you
// want instead.
//
// TASK
// Write `for_each` and two callbacks: `accumulate`, whose context is a
// `struct stats` (updates sum, min and max), and `print_indexed`, whose
// context is an `int` counter that it increments, printing
// "[index] value".
//
// EXPECTED OUTPUT
//     [0] 4
//     [1] -2
//     [2] 9
//     [3] 1
//     sum 12, min -2, max 9
//     printed 4 values

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

typedef void (*visit_fn)(int value, void *ctx);

struct stats {
    int sum;
    int min;
    int max;
};

void for_each(const int *a, size_t n, visit_fn f, void *ctx)
{
    // TODO
    (void)a;
    (void)n;
    (void)f;
    (void)ctx;
}

static void accumulate(int value, void *ctx)
{
    // TODO: ctx is a struct stats *
    (void)value;
    (void)ctx;
}

static void print_indexed(int value, void *ctx)
{
    // TODO: ctx is an int * holding the next index; print and increment.
    (void)value;
    (void)ctx;
}

int main(void)
{
    int values[] = {4, -2, 9, 1};
    size_t n = sizeof values / sizeof values[0];
    struct stats st = {0, INT_MAX, INT_MIN};
    int index = 0;

    for_each(values, n, print_indexed, &index);
    for_each(values, n, accumulate, &st);
    printf("sum %d, min %d, max %d\n", st.sum, st.min, st.max);
    printf("printed %d values\n", index);
    return 0;
}
