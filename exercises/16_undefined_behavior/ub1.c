// ub1.c
//
// CONCEPT
// *Undefined behavior* (UB) is the C standard saying "if a program does
// this, anything may happen". Not "the result is unspecified": the
// compiler is allowed to assume it never happens, and optimizes on that
// assumption. Code with UB can pass every test at -O0 and break at -O2,
// or work on x86 and fail on ARM, or work today and fail after a
// compiler upgrade. The sanitizers Clings runs catch many kinds at run
// time; this section walks through the ones that matter most.
//
// First: reading an *uninitialized* variable. A local declared without
// a value holds whatever was in that stack slot. gcc at -O0 often does
// not even warn, and the garbage is often 0, so the bug hides for
// years. The defenses: initialize at declaration, always; turn on
// -Wall -Wextra and, where available, -ftrivial-auto-var-init=pattern,
// which fills uninitialized locals with a recognizable byte pattern so
// the bug shows up immediately (Clings passes that flag for this
// exercise; that is why the output is wrong in a consistent way).
//
// WHEN YOU USE THIS
// Every declaration. `int total;` should make you flinch; `int total =
// 0;` should be the reflex.
//
// TASK
// Two variables are read before being set. Fix both declarations.
//
// EXPECTED OUTPUT
//     total: 60
//     largest: 30

#include <stdio.h>

int main(void)
{
    int values[] = {10, 30, 20};
    int total;
    int largest;

    for (int i = 0; i < 3; i++) {
        total += values[i];
        if (values[i] > largest) {
            largest = values[i];
        }
    }
    printf("total: %d\n", total);
    printf("largest: %d\n", largest);
    return 0;
}
