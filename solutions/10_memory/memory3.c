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
    size_t size = 64;
    char *buffer = malloc(size);

    if (buffer == NULL) {
        return NULL;
    }
    snprintf(buffer, size, "hello, %s", name);
    return buffer;
}

int main(void)
{
    char *greeting = make_greeting("Ada");

    if (greeting == NULL) {
        return 1;
    }
    printf("Greeting: %s\n", greeting);
    free(greeting);
    return 0;
}
