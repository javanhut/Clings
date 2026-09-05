// pointers8.c - solution

#include <stddef.h>
#include <stdio.h>

void skip_spaces(const char **cursor)
{
    while (**cursor == ' ') {
        (*cursor)++;
    }
}

void take_word(const char **cursor, char *out, size_t cap)
{
    size_t n = 0;

    while (**cursor != '\0' && **cursor != ' ') {
        if (n + 1 < cap) {
            out[n++] = **cursor;
        }
        (*cursor)++;
    }
    out[n] = '\0';
}

void choose(int **out, int *a, int *b)
{
    *out = (*a > *b) ? a : b;
}

int main(void)
{
    const char *text = "  hello   pointer world";
    const char *cursor = text;
    char word[16];

    for (int i = 0; i < 3; i++) {
        skip_spaces(&cursor);
        take_word(&cursor, word, sizeof(word));
        printf("word: '%s'\n", word);
    }
    skip_spaces(&cursor);
    printf("rest: '%s'\n", cursor);

    int a = 4;
    int b = 9;
    int *larger = NULL;
    choose(&larger, &a, &b);
    printf("larger is %d\n", *larger);
    return 0;
}
