// counter.c - support file for macros5; nothing to change here.

#include "counter.h"

// `static` at file scope: visible only inside this file. Other files
// cannot even declare it; the linker never sees the name.
static int total = 0;

// No `static`: this is an external definition, visible to every file
// that declares it with `extern` (counter.h does).
int bump_count = 0;

static void add_to_total(int amount)
{
    total += amount;
}

void counter_bump(int amount)
{
    add_to_total(amount);
    bump_count++;
}

int counter_value(void)
{
    return total;
}
