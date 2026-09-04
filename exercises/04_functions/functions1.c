// functions1.c
//
// The compiler reads a file from top to bottom. When it reaches the call
// to `greet()` in main, it has never heard of that function. Tell it about
// the function before it is used. Expected output:
//
//     Hello from a function!

#include <stdio.h>

int main(void)
{
    greet();
    return 0;
}

void greet(void)
{
    printf("Hello from a function!\n");
}
