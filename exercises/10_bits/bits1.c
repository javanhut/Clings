// bits1.c
//
// CONCEPT
// Integers are bit patterns, and C lets you work on the bits directly:
//
//     a & b    AND: 1 where both are 1         0b1100 & 0b1010 = 0b1000
//     a | b    OR:  1 where either is 1        0b1100 | 0b1010 = 0b1110
//     a ^ b    XOR: 1 where they differ        0b1100 ^ 0b1010 = 0b0110
//     ~a       NOT: flip every bit
//     a << n   shift left n places (multiply by 2^n)
//     a >> n   shift right n places (divide by 2^n, for unsigned)
//
// These are different from the *logical* operators `&&`, `||`, `!`, which
// treat their operands as true/false and produce 0 or 1. `flags & 4`
// tests bit 2; `flags && 4` is 1 whenever flags is non-zero. Mixing them
// up compiles fine and is wrong.
//
// Hex literals (0x0F) and, since C23, binary literals (0b1111) make bit
// patterns readable; printf's %x prints hex, %#x adds the 0x prefix.
// Do bit work on *unsigned* types: shifting signed values into or out of
// the sign bit is undefined or implementation-defined.
//
// WHEN YOU USE THIS
// Flags packed into one int (file permissions, socket options), hardware
// registers, network protocol headers, hashing, compression, graphics
// (pixel formats), anything where memory or bandwidth is measured in
// bits.
//
// TASK
// The program confuses logical and bitwise operators in three places.
// Fix them.
//
// EXPECTED OUTPUT
//     flags = 0x5
//     read: yes
//     write: no
//     read or write set: yes
//     flags with write: 0x7
//     flags without read: 0x4

#include <stdio.h>

#define PERM_READ 0x1u
#define PERM_WRITE 0x2u
#define PERM_EXEC 0x4u

int main(void)
{
    unsigned int flags = PERM_READ | PERM_EXEC;

    printf("flags = %#x\n", flags);
    printf("read: %s\n", (flags && PERM_READ) ? "yes" : "no");
    printf("write: %s\n", (flags && PERM_WRITE) ? "yes" : "no");
    printf("read or write set: %s\n", (flags & (PERM_READ || PERM_WRITE)) ? "yes" : "no");
    printf("flags with write: %#x\n", flags | PERM_WRITE);
    printf("flags without read: %#x\n", flags & ~PERM_READ);
    return 0;
}
