// types6.c
//
// CONCEPT
// `int` and `long` have platform-dependent sizes. When the exact width
// matters (a file format, a network protocol, a hash function, a register)
// use the types from <stdint.h>: int8_t, int16_t, int32_t, int64_t and their
// unsigned twins uint8_t ... uint64_t. They are exactly that many bits,
// everywhere. Their limits are INT32_MAX, UINT64_MAX and so on.
//
// printf needs to know the width too, and there is no portable letter for
// "64-bit". <inttypes.h> provides macros that expand to the right one:
//
//     printf("%" PRId64 "\n", x);   // x is int64_t
//     printf("%" PRIu32 "\n", y);   // y is uint32_t
//
// Adjacent string literals are glued together by the compiler, so
// "%" PRId64 "\n" becomes "%ld\n" on Linux and "%lld\n" on Windows.
//
// WHEN YOU USE THIS
// Anything that touches bytes on disk or on the wire, anything that must
// not overflow, embedded code where every bit is specified. Also as a
// habit: `uint8_t` says "a byte" much more clearly than `unsigned char`.
//
// TASK
// Two int32_t values are added. Their sum does not fit in 32 bits. Write
// the code that computes the sum in a 64-bit type (convert *before*
// adding, or the addition overflows, which is undefined behavior and the
// sanitizer will stop the program) and prints the three lines. Use sizeof
// for the sizes and the PRI macros for printing.
//
// EXPECTED OUTPUT
//     int32_t is 4 bytes, int64_t is 8 bytes
//     INT32_MAX = 2147483647
//     sum as int64_t = 4294967294

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int32_t a = INT32_MAX;
    int32_t b = INT32_MAX;

    // TODO: print the sizes, INT32_MAX, and a + b computed in 64 bits.
    (void)a;
    (void)b;
    return 0;
}
