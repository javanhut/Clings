// macros3.c
//
// CONCEPT
// Things only the preprocessor can do:
//
//   #x         *stringify*: turns the argument's text into a string
//              literal. `#define SHOW(e) printf(#e " = %d\n", e)` makes
//              `SHOW(a + b)` print `a + b = 7`. Adjacent string literals
//              are concatenated by the compiler.
//   a ## b     *token pasting*: glues two tokens into one identifier,
//              e.g. `#define HANDLER(name) handle_##name` gives
//              `handle_click`. Used to generate families of functions.
//   __FILE__, __LINE__, __func__
//              where you are; the basis of every ASSERT and LOG macro.
//   sizeof(a) / sizeof((a)[0])
//              the ARRAY_LEN macro, which only works on real arrays,
//              not on pointers (arrays4).
//   ...  and __VA_ARGS__
//              variadic macros: `#define LOG(fmt, ...) fprintf(stderr,
//              fmt, __VA_ARGS__)` forwards any number of arguments.
//
// WHEN YOU USE THIS
// Test frameworks (CHECK(x == 3) that prints the expression), logging
// with file and line, enum-to-string tables generated from a list,
// registering callbacks by name. The X-macro pattern (a list macro
// expanded several ways) is worth looking up once you are comfortable.
//
// TASK
// Write three macros:
//   ARRAY_LEN(a)      element count of an array
//   SHOW(expr)        prints "<expr text> = <value>" for an int expression
//   CHECK(cond)       prints "ok: <cond text>" when cond is true, or
//                     "FAIL: <cond text>" when it is false
//
// EXPECTED OUTPUT
//     values has 4 elements
//     a + b = 7
//     values[2] * 2 = 60
//     ok: a < b
//     FAIL: a == b
//     ok: ARRAY_LEN(values) == 4

#include <stdio.h>

// TODO: ARRAY_LEN, SHOW, CHECK

int main(void)
{
    int values[] = {10, 20, 30, 40};
    int a = 3;
    int b = 4;

    printf("values has %zu elements\n", ARRAY_LEN(values));
    SHOW(a + b);
    SHOW(values[2] * 2);
    CHECK(a < b);
    CHECK(a == b);
    CHECK(ARRAY_LEN(values) == 4);
    return 0;
}
