// strings9.c
//
// CONCEPT
// <ctype.h> classifies and converts single characters: isalpha, isdigit,
// isalnum, isspace, isupper, islower, toupper, tolower. They take an int
// that must be either EOF or a value representable as *unsigned char*. A
// plain `char` can be negative for bytes above 127 (UTF-8 text!), and
// passing a negative value is undefined behavior. Hence the idiom you
// see everywhere: `isalpha((unsigned char)c)`.
//
// A few everyday string algorithms:
//   - count words: a word starts where a non-space follows a space (or
//     the beginning). Track "was the previous char a space?"
//   - title case: upper-case the first letter of each word, lower-case
//     the rest. Same state machine.
//   - palindrome ignoring case and punctuation: two indices moving inward,
//     each skipping non-alphanumerics, comparing lower-cased chars.
//
// WHEN YOU USE THIS
// Text normalization before comparison or hashing, tokenizing, input
// validation. The "previous char" state machine pattern shows up in every
// hand-written lexer.
//
// TASK
// Write `count_words`, `title_case` (in place) and `is_palindrome`.
//
// EXPECTED OUTPUT
//     words: 5
//     words: 0
//     title: The Quick Brown Fox
//     palindrome("A man, a plan, a canal: Panama") = yes
//     palindrome("clings") = no
//     palindrome("") = yes

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int count_words(const char *s)
{
    // TODO: words are separated by one or more whitespace characters.
    (void)s;
    return -1;
}

void title_case(char *s)
{
    // TODO
    (void)s;
}

bool is_palindrome(const char *s)
{
    // TODO: ignore case and characters that are not letters or digits.
    (void)s;
    return false;
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
