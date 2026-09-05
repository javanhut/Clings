// project2.c - a string builder with printf-style appending
//
// THE PROJECT
// Write `strbuf`, a growable string: append raw text, append formatted
// text with a printf-like function, and hand the finished string back.
// Building strings piece by piece with correct sizing is one of the
// most common needs in C, and most projects carry a type like this.
//
// WHAT IT COMBINES
// realloc-based growth (11_memory), ownership with init/free
// (11_memory), snprintf's "returns the length it would need" contract
// (07_strings), and *variadic functions* from <stdarg.h>, which are new
// here:
//
//     #include <stdarg.h>
//     int strbuf_appendf(struct strbuf *sb, const char *fmt, ...)
//     {
//         va_list args;
//         va_start(args, fmt);            // start after the last named param
//         int n = vsnprintf(NULL, 0, fmt, args);   // measure
//         va_end(args);
//         ... grow so n + 1 bytes fit ...
//         va_start(args, fmt);            // a va_list can only be walked once
//         vsnprintf(sb->data + sb->len, n + 1, fmt, args);
//         va_end(args);
//         ...
//     }
//
// `...` in a parameter list accepts any number of extra arguments;
// va_list/va_start/va_end read them; the v-prefixed printf family
// (vprintf, vsnprintf) takes a va_list so you can forward them. This is
// how every logging function and every custom printf wrapper works.
//
// SUGGESTED STRUCTURE
//   struct strbuf { char *data; size_t len; size_t cap; };
//   strbuf_init, strbuf_reserve(sb, extra), strbuf_append(sb, text),
//   strbuf_appendf(sb, fmt, ...), strbuf_free. data is always a valid
//   string (terminated), even when empty (either allocate on init or
//   treat NULL as "").
//
// EXPECTED OUTPUT
//     [hello, world]
//     [hello, world! 3 + 4 = 7, pi ~ 3.14]
//     length 34, capacity >= 35: yes
//     [after clear]

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

// TODO: strbuf_init, strbuf_append, strbuf_appendf, strbuf_clear, strbuf_free

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
