// project2.c - solution

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strbuf {
    char *data;
    size_t len;
    size_t cap;
};

static void strbuf_init(struct strbuf *sb)
{
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

// Makes sure there is room for `extra` more bytes plus the terminator.
static bool strbuf_reserve(struct strbuf *sb, size_t extra)
{
    size_t needed = sb->len + extra + 1;

    if (needed <= sb->cap) {
        return true;
    }
    size_t new_cap = sb->cap == 0 ? 16 : sb->cap;
    while (new_cap < needed) {
        new_cap *= 2;
    }
    char *bigger = realloc(sb->data, new_cap);
    if (bigger == NULL) {
        return false;
    }
    if (sb->cap == 0) {
        bigger[0] = '\0';
    }
    sb->data = bigger;
    sb->cap = new_cap;
    return true;
}

static bool strbuf_append(struct strbuf *sb, const char *text)
{
    size_t n = strlen(text);

    if (!strbuf_reserve(sb, n)) {
        return false;
    }
    memcpy(sb->data + sb->len, text, n + 1);
    sb->len += n;
    return true;
}

static bool strbuf_appendf(struct strbuf *sb, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    int n = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if (n < 0 || !strbuf_reserve(sb, (size_t)n)) {
        return false;
    }
    va_start(args, fmt);
    vsnprintf(sb->data + sb->len, (size_t)n + 1, fmt, args);
    va_end(args);
    sb->len += (size_t)n;
    return true;
}

static void strbuf_clear(struct strbuf *sb)
{
    sb->len = 0;
    if (sb->data != NULL) {
        sb->data[0] = '\0';
    }
}

static void strbuf_free(struct strbuf *sb)
{
    free(sb->data);
    strbuf_init(sb);
}

int main(void)
{
    struct strbuf sb;

    strbuf_init(&sb);
    strbuf_append(&sb, "hello");
    strbuf_append(&sb, ", world");
    printf("[%s]\n", sb.data);
    strbuf_appendf(&sb, "! %d + %d = %d, pi ~ %.2f", 3, 4, 3 + 4, 3.14159);
    printf("[%s]\n", sb.data);
    printf("length %zu, capacity >= %zu: %s\n", sb.len, sb.len + 1,
           sb.cap >= sb.len + 1 ? "yes" : "no");
    strbuf_clear(&sb);
    strbuf_append(&sb, "after clear");
    printf("[%s]\n", sb.data);
    strbuf_free(&sb);
    return 0;
}
