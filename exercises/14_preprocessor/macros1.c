// macros1.c
//
// CONCEPT
// Before the compiler proper sees your code, the *preprocessor* runs
// over it as text. `#include` pastes a file in; `#define NAME value`
// replaces every later NAME with the text `value`; `#define SQUARE(x)
// ...` is a *function-like macro* that substitutes its argument
// textually. No types, no evaluation, just text.
//
// So `SQUARE(2 + 3)` with `#define SQUARE(x) x * x` becomes
// `2 + 3 * 2 + 3`, which is 11. The fix is parentheses around every use
// of a parameter *and* around the whole expansion:
//     #define SQUARE(x) ((x) * (x))
// Now `SQUARE(2 + 3)` is `((2 + 3) * (2 + 3))` and `1 / SQUARE(2)` is
// `1 / ((2) * (2))` rather than `1 / 2 * 2`.
//
// `gcc -E file.c` shows you the preprocessed output. Look at it when a
// macro misbehaves.
//
// WHEN YOU USE THIS
// Constants (`#define BUFFER_SIZE 4096`), small generic helpers
// (`MIN`, `ARRAY_LEN`), conditional compilation, and things a function
// cannot do: refer to the file and line, stringify an argument, build
// identifiers. For anything a `static inline` function can do, prefer
// the function: it has types, evaluates its arguments once, and shows
// up in the debugger.
//
// TASK
// Fix the macro definition (not the call!).
//
// EXPECTED OUTPUT
//     SQUARE(2 + 3) = 25
//     100 / SQUARE(5) = 4

#include <stdio.h>

#define SQUARE(x) x * x

int main(void)
{
    printf("SQUARE(2 + 3) = %d\n", SQUARE(2 + 3));
    printf("100 / SQUARE(5) = %d\n", 100 / SQUARE(5));
    return 0;
}
