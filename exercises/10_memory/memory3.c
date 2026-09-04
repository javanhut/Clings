// memory3.c
//
// Local variables live on the stack and disappear when their function
// returns. Returning a pointer to one is a bug: the memory is gone by the
// time the caller looks at it, and the compiler warns about it.
//
// Fix `make_greeting` by allocating the string on the heap with malloc
// (remember to free it in main). Expected output:
//
//     Greeting: hello, Ada

#include <stdio.h>
#include <stdlib.h>

char *make_greeting(const char *name)
{
    char buffer[64];

    snprintf(buffer, sizeof(buffer), "hello, %s", name);
    return buffer;
}

int main(void)
{
    char *greeting = make_greeting("Ada");

    printf("Greeting: %s\n", greeting);
    return 0;
}
