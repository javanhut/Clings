// strings3.c - solution

#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
    size_t len = strlen(s);

    for (size_t i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int main(void)
{
    char word[] = "clings";
    char one[] = "a";
    char empty[] = "";

    reverse(word);
    printf("reversed: %s\n", word);
    reverse(one);
    printf("reversed: %s\n", one);
    reverse(empty);
    printf("reversed: %s\n", empty);
    return 0;
}
