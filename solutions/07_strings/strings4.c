// strings4.c - solution

#include <stdio.h>

int count_vowels(const char *s)
{
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main(void)
{
    const char *word = "programming";

    printf("%s has %d vowels\n", word, count_vowels(word));
    return 0;
}
