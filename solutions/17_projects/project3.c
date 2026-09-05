// project3.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    double *items;
    size_t len;
    size_t cap;
};

static bool push(struct stack *s, double v)
{
    if (s->len == s->cap) {
        size_t new_cap = s->cap == 0 ? 8 : s->cap * 2;
        double *bigger = realloc(s->items, new_cap * sizeof *bigger);
        if (bigger == NULL) {
            return false;
        }
        s->items = bigger;
        s->cap = new_cap;
    }
    s->items[s->len++] = v;
    return true;
}

static bool pop(struct stack *s, double *out)
{
    if (s->len == 0) {
        return false;
    }
    *out = s->items[--s->len];
    return true;
}

static bool parse_number(const char *tok, double *out)
{
    char *end;
    double v = strtod(tok, &end);

    if (end == tok || *end != '\0') {
        return false;
    }
    *out = v;
    return true;
}

// Evaluates one line. On success stores the value; on failure stores a
// message in *error. Modifies line (strtok).
static bool eval_line(char *line, double *result, const char **error)
{
    struct stack s = {NULL, 0, 0};
    bool ok = true;
    size_t tokens = 0;

    for (char *tok = strtok(line, " \t\n"); tok != NULL && ok; tok = strtok(NULL, " \t\n")) {
        double v;
        tokens++;
        if (parse_number(tok, &v)) {
            ok = push(&s, v);
            continue;
        }
        if (strlen(tok) != 1 || strchr("+-*/", tok[0]) == NULL) {
            *error = "unknown token";
            ok = false;
            break;
        }
        double b;
        double a;
        if (!pop(&s, &b) || !pop(&s, &a)) {
            *error = "stack underflow";
            ok = false;
            break;
        }
        switch (tok[0]) {
        case '+':
            v = a + b;
            break;
        case '-':
            v = a - b;
            break;
        case '*':
            v = a * b;
            break;
        default:
            if (b == 0) {
                *error = "division by zero";
                ok = false;
            } else {
                v = a / b;
            }
            break;
        }
        if (ok) {
            ok = push(&s, v);
        }
    }

    if (ok) {
        if (tokens == 0) {
            *error = "empty";
            ok = false;
        } else if (s.len > 1) {
            *error = "too many values";
            ok = false;
        } else if (s.len == 1) {
            *result = s.items[0];
        }
    }
    free(s.items);
    return ok;
}

int main(void)
{
    char line[256];
    int failures = 0;

    while (fgets(line, sizeof line, stdin) != NULL) {
        char copy[256];
        strcpy(copy, line);
        double result = 0;
        const char *error = NULL;
        if (eval_line(line, &result, &error)) {
            printf("%g\n", result);
        } else {
            if (strcmp(error, "unknown token") == 0) {
                // Find the offending token again in the untouched copy.
                for (char *tok = strtok(copy, " \t\n"); tok != NULL; tok = strtok(NULL, " \t\n")) {
                    double v;
                    if (!parse_number(tok, &v) && (strlen(tok) != 1 || strchr("+-*/", tok[0]) == NULL)) {
                        printf("error: unknown token: %s\n", tok);
                        break;
                    }
                }
            } else {
                printf("error: %s\n", error);
            }
            failures++;
        }
    }
    return failures > 0 ? 1 : 0;
}
