// project1.c - solution

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 64

struct entry {
    char *word;
    int count;
};

struct table {
    struct entry *items;
    size_t len;
    size_t cap;
};

static bool table_bump(struct table *t, const char *word)
{
    for (size_t i = 0; i < t->len; i++) {
        if (strcmp(t->items[i].word, word) == 0) {
            t->items[i].count++;
            return true;
        }
    }
    if (t->len == t->cap) {
        size_t new_cap = t->cap == 0 ? 16 : t->cap * 2;
        struct entry *bigger = realloc(t->items, new_cap * sizeof *bigger);
        if (bigger == NULL) {
            return false;
        }
        t->items = bigger;
        t->cap = new_cap;
    }
    size_t size = strlen(word) + 1;
    char *copy = malloc(size);
    if (copy == NULL) {
        return false;
    }
    memcpy(copy, word, size);
    t->items[t->len].word = copy;
    t->items[t->len].count = 1;
    t->len++;
    return true;
}

static void table_free(struct table *t)
{
    for (size_t i = 0; i < t->len; i++) {
        free(t->items[i].word);
    }
    free(t->items);
    t->items = NULL;
    t->len = 0;
    t->cap = 0;
}

// Copies the next word starting at *cursor into buf (lower-cased) and
// advances *cursor past it. Returns false when there are no more words.
static bool next_word(const char **cursor, char *buf, size_t cap)
{
    const char *p = *cursor;

    while (*p != '\0' && !isalnum((unsigned char)*p)) {
        p++;
    }
    if (*p == '\0') {
        *cursor = p;
        return false;
    }
    size_t n = 0;
    while (isalnum((unsigned char)*p)) {
        if (n + 1 < cap) {
            buf[n++] = (char)tolower((unsigned char)*p);
        }
        p++;
    }
    buf[n] = '\0';
    *cursor = p;
    return true;
}

static int by_count_then_word(const void *a, const void *b)
{
    const struct entry *x = a;
    const struct entry *y = b;

    if (x->count != y->count) {
        return y->count - x->count;
    }
    return strcmp(x->word, y->word);
}

int main(int argc, char *argv[])
{
    struct table t = {NULL, 0, 0};
    char line[512];
    char word[MAX_WORD];
    long top = 5;

    if (argc > 1) {
        top = strtol(argv[1], NULL, 10);
        if (top <= 0) {
            top = 5;
        }
    }

    while (fgets(line, sizeof line, stdin) != NULL) {
        const char *cursor = line;
        while (next_word(&cursor, word, sizeof word)) {
            if (!table_bump(&t, word)) {
                fprintf(stderr, "out of memory\n");
                table_free(&t);
                return 1;
            }
        }
    }

    qsort(t.items, t.len, sizeof t.items[0], by_count_then_word);
    for (size_t i = 0; i < t.len && i < (size_t)top; i++) {
        printf("%s: %d\n", t.items[i].word, t.items[i].count);
    }
    printf("(%zu distinct words)\n", t.len);
    table_free(&t);
    return 0;
}
