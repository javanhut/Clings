// if1.c
//
// A classic C mistake: `=` assigns, `==` compares. The condition below
// assigns 5 to x (which is "true" because it is not zero), so the wrong
// branch runs. Fix the comparison so the program prints:
//
//     x is not five

#include <stdio.h>

int main(void)
{
    int x = 3;

    if (x == 5) {
        printf("x is five\n");
    } else {
        printf("x is not five\n");
    }
    return 0;
}
