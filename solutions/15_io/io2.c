// io2.c - solution

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool parse_int(const char *text, int *out)
{
    char *end;

    errno = 0;
    long v = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        return false;
    }
    *out = (int)v;
    return true;
}

int main(int argc, char *argv[])
{
    int sum = 0;
    int invalid = 0;

    for (int i = 1; i < argc; i++) {
        int v;
        if (parse_int(argv[i], &v)) {
            sum += v;
        } else {
            fprintf(stderr, "invalid number: %s\n", argv[i]);
            invalid++;
        }
    }
    printf("sum of valid arguments: %d\n", sum);
    return invalid;
}
