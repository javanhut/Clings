// switch1.c
//
// CONCEPT
// `switch (value)` jumps to the `case` label matching the value (which
// must be an integer constant: numbers, characters, enum values) and then
// keeps executing *downwards* through the following cases until it hits a
// `break` or the end of the switch. This "fallthrough" is deliberate,
// occasionally useful, and the source of endless bugs when a `break` is
// forgotten. `default:` runs when nothing matches.
//
// WHEN YOU USE THIS
// Dispatching on an enum or a command character, state machines, byte
// code interpreters. A switch over an enum has a bonus: with -Wall the
// compiler warns if you forget a value (as long as there is no `default`,
// which would silence it).
//
// TASK
// The program should print only the name of day 3 but prints several
// lines. Fix it.
//
// EXPECTED OUTPUT
//     Wednesday

#include <stdio.h>

int main(void)
{
    int day = 3;

    switch (day) {
    case 1:
        printf("Monday\n");
    case 2:
        printf("Tuesday\n");
    case 3:
        printf("Wednesday\n");
    case 4:
        printf("Thursday\n");
    case 5:
        printf("Friday\n");
    default:
        printf("Weekend\n");
    }
    return 0;
}
