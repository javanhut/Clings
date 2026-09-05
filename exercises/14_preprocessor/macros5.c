// macros5.c
//
// CONCEPT
// *Linkage* decides which names are visible across .c files.
//
//   - A function or global variable defined at file scope without
//     `static` has *external linkage*: the linker can connect a use in
//     one file to the definition in another. To use it, a file needs a
//     *declaration*: a prototype for functions, `extern int x;` for
//     variables. Those go in the module's header.
//   - With `static`, it has *internal linkage*: private to its file.
//     Other files cannot reach it at all. Helpers that are not part of
//     the interface should be static; it prevents name clashes between
//     files and tells the reader what the public surface is.
//   - `extern int x;` declares without defining (no storage). Exactly
//     one .c file must contain the definition `int x = 0;`. A definition
//     in a header would be duplicated in every file that includes it
//     and fail to link.
//
// Errors from getting this wrong come in two flavors: the *compiler*
// says "implicit declaration of function" when it has not seen a
// prototype; the *linker* says "undefined reference to `name'" when no
// compiled file defines it (or it is static in another file).
//
// WHEN YOU USE THIS
// Every multi-file program. The habit: one .h per .c module with the
// public prototypes and extern declarations; everything else in the .c
// marked static.
//
// TASK
// This file uses counter.c without including its header, and calls a
// function that counter.c keeps private. Include the header, and make
// the "reset" work through the public interface instead of touching
// `total` (hint: what can you bump by?).
//
// EXPECTED OUTPUT
//     value: 30
//     bumps: 2
//     value after reset: 0
//     bumps: 3

#include <stdio.h>

int main(void)
{
    counter_bump(10);
    counter_bump(20);
    printf("value: %d\n", counter_value());
    printf("bumps: %d\n", bump_count);

    add_to_total(-total);
    printf("value after reset: %d\n", counter_value());
    printf("bumps: %d\n", bump_count);
    return 0;
}
