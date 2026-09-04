// strings2.c
//
// `==` on two strings compares their addresses, not their contents, so two
// different copies of "yes" are never "equal". Use the right function from
// <string.h> to compare the contents. Expected output:
//
//     Confirmed

#include <stdio.h>
#include <string.h>

int main(void)
{
    char answer[] = "yes";

    if (answer == "yes") {
        printf("Confirmed\n");
    } else {
        printf("Not confirmed\n");
    }
    return 0;
}
