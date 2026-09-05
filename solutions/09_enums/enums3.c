// enums3.c - solution

#include <stdio.h>

enum door_state {
    CLOSED,
    OPEN,
    LOCKED,
};

const char *state_name(enum door_state s)
{
    switch (s) {
    case CLOSED:
        return "closed";
    case OPEN:
        return "open";
    case LOCKED:
        return "locked";
    }
    return "?";
}

enum door_state next_state(enum door_state s, char event)
{
    switch (s) {
    case CLOSED:
        if (event == 'o') {
            return OPEN;
        }
        if (event == 'l') {
            return LOCKED;
        }
        return s;
    case OPEN:
        return event == 'c' ? CLOSED : s;
    case LOCKED:
        return event == 'u' ? CLOSED : s;
    }
    return s;
}

void run(const char *events)
{
    enum door_state s = CLOSED;

    printf("start: %s\n", state_name(s));
    for (const char *e = events; *e != '\0'; e++) {
        enum door_state next = next_state(s, *e);
        printf("%c: %s -> %s\n", *e, state_name(s), state_name(next));
        s = next;
    }
    printf("end: %s\n", state_name(s));
}

int main(void)
{
    run("olclou");
    return 0;
}
