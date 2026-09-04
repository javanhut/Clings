// loops2.c
//
// `break` leaves a loop entirely; `continue` skips to the next iteration.
// This program should print the even numbers from 1 to 10, one per line:
//
//     2
//     4
//     6
//     8
//     10
//
// but it prints nothing at all. Fix it.

#include <stdio.h>

int main(void)
{
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 1) {
            break;
        }
        printf("%d\n", i);
    }
    return 0;
}
