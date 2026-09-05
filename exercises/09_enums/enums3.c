// enums3.c
//
// CONCEPT
// A *state machine* is a current state (an enum) plus a function that,
// given the state and an event, returns the next state. Everything
// interesting about the system lives in that one function, usually a
// `switch` on the state with an inner `switch` or `if` on the event.
// Unknown events leave the state unchanged.
//
// A door with a lock:
//
//     state    event   -> next state
//     CLOSED   'o'     -> OPEN
//     CLOSED   'l'     -> LOCKED
//     OPEN     'c'     -> CLOSED
//     LOCKED   'u'     -> CLOSED
//     anything else    -> same state
//
// WHEN YOU USE THIS
// Protocol handling (TCP is a state machine), parsers and lexers, UI
// flows, game logic, embedded controllers. Enum + switch keeps all the
// transitions in one readable place, and the compiler's missing-case
// warning helps when a state is added.
//
// TASK
// Write `state_name` and `next_state` for the door above, then complete
// `run`, which feeds every character of `events` through next_state and
// prints one line per event as shown (the arrow line format is
// "<event>: <old> -> <new>").
//
// EXPECTED OUTPUT
//     start: closed
//     o: closed -> open
//     l: open -> open
//     c: open -> closed
//     l: closed -> locked
//     o: locked -> locked
//     u: locked -> closed
//     end: closed

#include <stdio.h>

enum door_state {
    CLOSED,
    OPEN,
    LOCKED,
};

const char *state_name(enum door_state s)
{
    // TODO
    (void)s;
    return "?";
}

enum door_state next_state(enum door_state s, char event)
{
    // TODO
    (void)event;
    return s;
}

void run(const char *events)
{
    enum door_state s = CLOSED;

    printf("start: %s\n", state_name(s));
    // TODO: for each event, compute the next state and print the line.
    (void)events;
    printf("end: %s\n", state_name(s));
}

int main(void)
{
    run("olclou");
    return 0;
}
