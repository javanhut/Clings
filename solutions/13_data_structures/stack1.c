// stack1.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
    char *items;
    size_t len;
    size_t cap;
};

bool stack_push(struct stack *s, char c)
{
    if (s->len == s->cap) {
        size_t new_cap = s->cap == 0 ? 8 : s->cap * 2;
        char *bigger = realloc(s->items, new_cap);
        if (bigger == NULL) {
            return false;
        }
        s->items = bigger;
        s->cap = new_cap;
    }
    s->items[s->len++] = c;
    return true;
}

bool stack_pop(struct stack *s, char *out)
{
    if (s->len == 0) {
        return false;
    }
    *out = s->items[--s->len];
    return true;
}

void stack_free(struct stack *s)
{
    free(s->items);
    s->items = NULL;
    s->len = 0;
    s->cap = 0;
}

static char closer_of(char opener)
{
    switch (opener) {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    default:
        return '\0';
    }
}

bool balanced(const char *text)
{
    struct stack s = {NULL, 0, 0};
    bool ok = true;

    for (const char *p = text; *p != '\0' && ok; p++) {
        char c = *p;
        if (c == '(' || c == '[' || c == '{') {
            if (!stack_push(&s, c)) {
                ok = false;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            char opener;
            ok = stack_pop(&s, &opener) && closer_of(opener) == c;
        }
    }
    if (s.len != 0) {
        ok = false;
    }
    stack_free(&s);
    return ok;
}

int main(void)
{
    const char *samples[] = {"{[()]}", "([)]", "((", "", "a(b)c[d]{e}"};

    for (size_t i = 0; i < 5; i++) {
        printf("\"%s\" balanced: %s\n", samples[i], balanced(samples[i]) ? "yes" : "no");
    }
    return 0;
}
