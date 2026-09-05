// strings9.c - solution

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int count_words(const char *s)
{
    int words = 0;
    bool in_space = true;

    for (; *s != '\0'; s++) {
        bool space = isspace((unsigned char)*s);
        if (in_space && !space) {
            words++;
        }
        in_space = space;
    }
    return words;
}

void title_case(char *s)
{
    bool start = true;

    for (; *s != '\0'; s++) {
        unsigned char c = (unsigned char)*s;
        if (isspace(c)) {
            start = true;
        } else if (start) {
            *s = (char)toupper(c);
            start = false;
        } else {
            *s = (char)tolower(c);
        }
    }
}

bool is_palindrome(const char *s)
{
    size_t len = strlen(s);
    size_t i = 0;
    size_t j = len;

    while (i < j) {
        if (!isalnum((unsigned char)s[i])) {
            i++;
            continue;
        }
        if (!isalnum((unsigned char)s[j - 1])) {
            j--;
            continue;
        }
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j - 1])) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main(void)
{
    char text[] = "the QUICK brown fox";

    printf("words: %d\n", count_words("  the quick  brown fox jumps "));
    printf("words: %d\n", count_words("   "));
    title_case(text);
    printf("title: %s\n", text);
    printf("palindrome(\"A man, a plan, a canal: Panama\") = %s\n",
           is_palindrome("A man, a plan, a canal: Panama") ? "yes" : "no");
    printf("palindrome(\"clings\") = %s\n", is_palindrome("clings") ? "yes" : "no");
    printf("palindrome(\"\") = %s\n", is_palindrome("") ? "yes" : "no");
    return 0;
}
