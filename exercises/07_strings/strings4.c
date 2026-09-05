// strings4.c
//
// CONCEPT
// `c == 'a' || 'e'` does not mean "c is a or e". It parses as
// `(c == 'a') || ('e')`, and 'e' on its own is the number 101, which is
// true. So the whole condition is always true. Each comparison has to be
// spelled out: `c == 'a' || c == 'e' || ...`. Compilers warn about this
// one now, but only for the simplest shapes.
//
// For "is c one of these characters", `strchr("aeiou", c) != NULL` is a
// compact alternative (careful: strchr also matches the '\0' at the end
// of the set, so check c != '\0' first if it can occur).
//
// WHEN YOU USE THIS
// Character classification is everywhere in parsing. <ctype.h> covers the
// standard classes (isalpha, isdigit, isspace, ...); for custom sets you
// write comparisons or use strchr.
//
// TASK
// Fix the condition.
//
// EXPECTED OUTPUT
//     programming has 3 vowels

#include <stdio.h>

int count_vowels(const char *s)
{
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'a' || 'e' || 'i' || 'o' || 'u') {
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
