// strings8.c - solution

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_int(const char *text, int *out)
{
    char *end;

    errno = 0;
    long v = strtol(text, &end, 10);
    if (end == text || *end != '\0') {
        return false;
    }
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        return false;
    }
    *out = (int)v;
    return true;
}

int sum_csv(char *line)
{
    int sum = 0;

    for (char *tok = strtok(line, ","); tok != NULL; tok = strtok(NULL, ",")) {
        int v;
        if (parse_int(tok, &v)) {
            sum += v;
        } else {
            printf("bad token: %s\n", tok);
        }
    }
    return sum;
}

static void try_parse(const char *text)
{
    int v;
    if (parse_int(text, &v)) {
        printf("parse \"%s\" -> ok %d\n", text, v);
    } else {
        printf("parse \"%s\" -> error\n", text);
    }
}

int main(void)
{
    char line[] = "10,20,x,30,4.5";

    try_parse("42");
    try_parse("-7");
    try_parse("12abc");
    try_parse("");
    try_parse("99999999999");
    printf("sum = %d\n", sum_csv(line));
    return 0;
}
