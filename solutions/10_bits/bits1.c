// bits1.c - solution

#include <stdio.h>

#define PERM_READ 0x1u
#define PERM_WRITE 0x2u
#define PERM_EXEC 0x4u

int main(void)
{
    unsigned int flags = PERM_READ | PERM_EXEC;

    printf("flags = %#x\n", flags);
    printf("read: %s\n", (flags & PERM_READ) ? "yes" : "no");
    printf("write: %s\n", (flags & PERM_WRITE) ? "yes" : "no");
    printf("read or write set: %s\n", (flags & (PERM_READ | PERM_WRITE)) ? "yes" : "no");
    printf("flags with write: %#x\n", flags | PERM_WRITE);
    printf("flags without read: %#x\n", flags & ~PERM_READ);
    return 0;
}
