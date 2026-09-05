// strings6.c - solution

#include <stddef.h>
#include <stdio.h>

size_t my_strlen(const char *s)
{
    size_t n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
}

char *my_strcpy(char *dst, const char *src)
{
    size_t i = 0;

    do {
        dst[i] = src[i];
    } while (src[i++] != '\0');
    return dst;
}

int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

char *my_strcat(char *dst, const char *src)
{
    my_strcpy(dst + my_strlen(dst), src);
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
