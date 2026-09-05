// strings6.c
//
// CONCEPT
// The string functions in <string.h> are all short loops over the
// terminator. Writing them yourself once is the best way to understand
// what they do and what they assume:
//
//     strlen(s)        count until '\0'
//     strcpy(dst, src) copy each char including the '\0'; dst must be big
//                      enough (it cannot check!)
//     strcmp(a, b)     walk both while they are equal and not at the end,
//                      then return the difference of the first mismatching
//                      characters (as unsigned char, so bytes > 127 sort
//                      after ASCII)
//     strcat(dst, src) find the end of dst, then strcpy src there
//
// Real implementations use pointer loops like `while ((*dst++ = *src++))
// ;`, which is famous, terse and correct: assign, test the assigned char,
// advance both. You may write the index version; do read the pointer one
// until you can explain it.
//
// WHEN YOU USE THIS
// You will not replace the library, but you will write variants: copy up
// to a delimiter, compare case-insensitively, length of a string that
// might not be terminated (strnlen). Those are the same loops with one
// twist each.
//
// TASK
// Implement my_strlen, my_strcpy (returns dst), my_strcmp and my_strcat
// (returns dst) without calling any <string.h> function.
//
// EXPECTED OUTPUT
//     len("clings") = 6
//     len("") = 0
//     copy: clings
//     cmp("abc", "abc") = 0
//     cmp("abc", "abd") < 0
//     cmp("b", "abc") > 0
//     cmp("abc", "ab") > 0
//     cat: clings rocks

#include <stddef.h>
#include <stdio.h>

size_t my_strlen(const char *s)
{
    // TODO
    (void)s;
    return 0;
}

char *my_strcpy(char *dst, const char *src)
{
    // TODO
    (void)src;
    return dst;
}

int my_strcmp(const char *a, const char *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

char *my_strcat(char *dst, const char *src)
{
    // TODO
    (void)src;
    return dst;
}

static const char *sign(int v)
{
    return v < 0 ? "< 0" : v > 0 ? "> 0" : "= 0";
}

int main(void)
{
    char buf[32];

    printf("len(\"clings\") = %zu\n", my_strlen("clings"));
    printf("len(\"\") = %zu\n", my_strlen(""));
    printf("copy: %s\n", my_strcpy(buf, "clings"));
    printf("cmp(\"abc\", \"abc\") %s\n", sign(my_strcmp("abc", "abc")));
    printf("cmp(\"abc\", \"abd\") %s\n", sign(my_strcmp("abc", "abd")));
    printf("cmp(\"b\", \"abc\") %s\n", sign(my_strcmp("b", "abc")));
    printf("cmp(\"abc\", \"ab\") %s\n", sign(my_strcmp("abc", "ab")));
    printf("cat: %s\n", my_strcat(buf, " rocks"));
    return 0;
}
