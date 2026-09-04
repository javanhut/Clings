// types4.c
//
// Before C23, `bool`, `true` and `false` are not built into the language.
// They come from a standard header. This exercise is compiled as C17, so
// include the right header to make it work. Expected output:
//
//     Ready!

#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool ready = true;

    if (ready) {
        printf("Ready!\n");
    }
    return 0;
}
