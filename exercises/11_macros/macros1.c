// macros1.c
//
// A macro is a textual substitution done by the preprocessor before the
// compiler sees the code. `SQUARE(2 + 3)` below becomes `2 + 3 * 2 + 3`,
// which is 11, not 25. Fix the macro definition (not the call!) so that
// the program prints:
//
//     SQUARE(2 + 3) = 25

#include <stdio.h>

#define SQUARE(x) x * x

int main(void)
{
    printf("SQUARE(2 + 3) = %d\n", SQUARE(2 + 3));
    return 0;
}
