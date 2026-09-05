// pointers4.c - solution

#include <stdio.h>
#include <string.h>

void print_length(const char *s)
{
    if (s == NULL) {
        printf("(null)\n");
        return;
    }
    printf("%s has length %zu\n", s, strlen(s));
}

int main(void)
{
    print_length("hello");
    print_length(NULL);
    return 0;
}
