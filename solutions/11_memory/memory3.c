// memory3.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns a heap-allocated string; the caller must free it.
char *make_greeting(const char *name)
{
    size_t size = strlen("hello, ") + strlen(name) + 1;
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
