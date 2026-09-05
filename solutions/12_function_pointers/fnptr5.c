// fnptr5.c - solution

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
    for (size_t i = 0; i < n; i++) {
        f(a[i], ctx);
    }
}

static void accumulate(int value, void *ctx)
{
    struct stats *st = ctx;

    st->sum += value;
    if (value < st->min) {
        st->min = value;
    }
    if (value > st->max) {
        st->max = value;
    }
}

static void print_indexed(int value, void *ctx)
{
    int *index = ctx;

    printf("[%d] %d\n", *index, value);
    (*index)++;
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
