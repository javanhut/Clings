// io3.c - solution

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[256];
    char longest[256] = "";
    size_t longest_len = 0;
    int lines = 0;
    int words = 0;
    long chars = 0;

    while (fgets(line, sizeof line, stdin) != NULL) {
        lines++;
        chars += (long)strlen(line);

        bool in_word = false;
        for (const char *p = line; *p != '\0'; p++) {
            bool space = isspace((unsigned char)*p);
            if (!space && !in_word) {
                words++;
            }
            in_word = !space;
        }

        line[strcspn(line, "\n")] = '\0';
        size_t len = strlen(line);
        if (len > longest_len) {
            longest_len = len;
            strcpy(longest, line);
        }
    }
    printf("lines: %d\n", lines);
    printf("words: %d\n", words);
    printf("chars: %ld\n", chars);
    printf("longest (%zu): %s\n", longest_len, longest);
    return 0;
}
