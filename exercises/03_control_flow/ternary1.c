// ternary1.c
//
// CONCEPT
// `condition ? a : b` is an *expression* that evaluates to a when the
// condition is true and b otherwise. It is the only way in C to choose a
// value inline, for example inside a printf argument or an initializer:
//
//     const char *label = count == 1 ? "item" : "items";
//     int larger = a > b ? a : b;
//
// It is not a replacement for `if`: use it when you are producing a value,
// not when you are doing things. Nesting ternaries is legal and unreadable.
//
// Also in this exercise: `goto`. It jumps to a label in the same function.
// In C, it has one respectable use: jumping to cleanup code at the end of
// a function when something fails in the middle, instead of duplicating
// the cleanup in every error branch. You will see `goto fail;` and
// `goto out;` throughout the Linux kernel and most C libraries.
//
// WHEN YOU USE THIS
// Ternary: min/max, pluralization, picking a string for a flag. goto: the
// cleanup pattern, and nothing else.
//
// TASK
// 1. Write `max3` using only ternary expressions (no if).
// 2. Write `plural`: returns "s" when n != 1 and "" otherwise.
// 3. In `process`, the three steps are attempted in order. Replace the
//    repeated cleanup with a single `cleanup:` label at the end and jump to
//    it with goto when a step fails. The behavior must stay the same.
//
// EXPECTED OUTPUT
//     max3(3, 9, 5) = 9
//     max3(-1, -7, -3) = -1
//     1 item, 2 items, 0 items
//     step 1 ok
//     step 2 failed
//     cleanup done
//     process(2) returned -1
//     step 1 ok
//     step 2 ok
//     step 3 ok
//     cleanup done
//     process(4) returned 0

#include <stdio.h>

int max3(int a, int b, int c)
{
    // TODO: ternary only.
    (void)a;
    (void)b;
    (void)c;
    return 0;
}

const char *plural(int n)
{
    // TODO
    (void)n;
    return "";
}

// Fails at step `fail_at`; steps are numbered 1, 2, 3.
int process(int fail_at)
{
    // TODO: rewrite with one cleanup label and goto.
    if (fail_at == 1) {
        printf("step 1 failed\n");
        printf("cleanup done\n");
        return -1;
    }
    printf("step 1 ok\n");
    if (fail_at == 2) {
        printf("step 2 failed\n");
        printf("cleanup done\n");
        return -1;
    }
    printf("step 2 ok\n");
    if (fail_at == 3) {
        printf("step 3 failed\n");
        printf("cleanup done\n");
        return -1;
    }
    printf("step 3 ok\n");
    printf("cleanup done\n");
    return 0;
}

int main(void)
{
    printf("max3(3, 9, 5) = %d\n", max3(3, 9, 5));
    printf("max3(-1, -7, -3) = %d\n", max3(-1, -7, -3));
    printf("1 item%s, 2 item%s, 0 item%s\n", plural(1), plural(2), plural(0));
    printf("process(2) returned %d\n", process(2));
    printf("process(4) returned %d\n", process(4));
    return 0;
}
