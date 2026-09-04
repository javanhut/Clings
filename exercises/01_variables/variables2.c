// variables2.c
//
// A variable declared `const` cannot be changed after it is initialized.
// This program tries to do exactly that. Fix it so that it counts to 5
// and prints:
//
//     count is 5

#include <stdio.h>

int main(void)
{
    const int count = 0;

    for (int i = 0; i < 5; i++) {
        count = count + 1;
    }

    printf("count is %d\n", count);
    return 0;
}
