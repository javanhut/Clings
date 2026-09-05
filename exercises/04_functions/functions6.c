// functions6.c
//
// CONCEPT
// Normally a local variable is created when its function is entered and
// destroyed when the function returns. A local declared `static` is
// different: it is created once, before the program starts, and keeps its
// value between calls. It is initialized once (to 0 if you say nothing),
// not every call.
//
//     int next_id(void)
//     {
//         static int counter = 0;   // survives between calls
//         counter++;
//         return counter;
//     }
//
// A variable declared *outside* every function is a global: visible to
// every function in the file (and, unless marked `static`, to other files
// too; the preprocessor section covers that). Globals are the easy way to
// share state and the easy way to make programs impossible to reason
// about. Prefer passing things as arguments; reach for a global only for
// genuinely program-wide state such as a configuration or a logger.
//
// WHEN YOU USE THIS
// Static locals: one-time initialization ("has this been set up yet?"),
// counters, caches. The standard library uses them too (strtok keeps its
// position in one, which is why it is not safe with threads).
//
// TASK
// Write `next_id` so it returns 1, 2, 3, ... on successive calls using a
// static local, and `reset_ids` so the next call to next_id returns 1
// again. Since a static *local* is invisible outside its function, the two
// functions must share a file-scope variable instead. Put it above them,
// marked `static` so it is private to this file.
//
// EXPECTED OUTPUT
//     ids: 1 2 3
//     after reset: 1 2

#include <stdio.h>

// TODO: shared counter here.

int next_id(void)
{
    // TODO
    return 0;
}

void reset_ids(void)
{
    // TODO
}

int main(void)
{
    // C does not define the order in which the arguments of one call are
    // evaluated, so printf("%d %d", next_id(), next_id()) could print
    // "2 1". Calls with side effects go into separate statements.
    int a = next_id();
    int b = next_id();
    int c = next_id();
    printf("ids: %d %d %d\n", a, b, c);
    reset_ids();
    int d = next_id();
    int e = next_id();
    printf("after reset: %d %d\n", d, e);
    return 0;
}
