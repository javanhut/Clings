// pointers7.c - solution

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void shout(const char *s)
{
    printf("shout: ");
    for (size_t i = 0; s[i] != '\0'; i++) {
        putchar(toupper((unsigned char)s[i]));
    }
    printf("\n");
}

size_t length(const char *s)
{
    return strlen(s);
}

int main(void)
{
    const char *word = "hello";
    int a = 1;
    int b = 5;
    int *const fixed = &a;

    shout(word);
    printf("length: %zu\n", length("hello"));
    *fixed += b;
    printf("total: %d\n", *fixed);
    return 0;
}
