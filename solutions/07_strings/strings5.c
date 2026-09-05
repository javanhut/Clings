// strings5.c - solution

#include <ctype.h>
#include <stdio.h>

void capitalize(char *s)
{
    if (s[0] != '\0') {
        s[0] = (char)toupper((unsigned char)s[0]);
    }
}

void print_twice(const char *greeting)
{
    printf("%s\n%s\n", greeting, greeting);
}

int main(void)
{
    char word[] = "hello";

    capitalize(word);
    print_twice(word);
    return 0;
}
