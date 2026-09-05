// bits4.c
//
// CONCEPT
// Shifts have sharp edges in C:
//
//   - Shifting by the width of the type or more (`x << 32` for a 32-bit
//     x) is undefined behavior, on every type. The CPU may mask the count
//     to 5 bits and do `x << 0`, or do something else entirely.
//   - Left-shifting a *signed* value so that a 1 lands in or beyond the
//     sign bit is undefined: `1 << 31` on int. Write `1u << 31`.
//   - Right-shifting a negative signed value is implementation-defined
//     (arithmetic shift on every mainstream compiler, but not promised).
//   - A literal like `1` is an int. `1 << 40` overflows even if you assign
//     the result to a uint64_t; the shift happens in int first. Write
//     `(uint64_t)1 << 40` or `UINT64_C(1) << 40`.
//   - Integer promotion: operands smaller than int (uint8_t, uint16_t)
//     become *int* before the operation. `~(uint8_t)0` is -1, not 255.
//     Mask the result back: `(uint8_t)~x` or `~x & 0xFF`.
//
// UndefinedBehaviorSanitizer reports each of these at run time; Clings
// has it on, so run this file as is and read the reports.
//
// WHEN YOU USE THIS
// Every bit-manipulation routine. The habit that prevents all of the
// above: do bit work on unsigned types of the width you mean, with
// literals suffixed `u` or cast to that width.
//
// TASK
// Fix the four problems so the program runs without sanitizer errors and
// prints the expected output. The printed values are what the code is
// obviously *trying* to compute.
//
// EXPECTED OUTPUT
//     top bit: 0x80000000
//     bit 40: 0x10000000000
//     inverted byte: 0xf0
//     low 3 bits of 0xff: 0x7

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// Returns a mask with the lowest `n` bits set, for n in 0..32.
uint32_t low_bits(unsigned int n)
{
    return (1u << n) - 1;
}

int main(void)
{
    int top = 1 << 31;
    uint64_t bit40 = 1 << 40;
    uint8_t byte = 0x0f;
    uint8_t inverted = ~byte;

    printf("top bit: %#x\n", (unsigned int)top);
    printf("bit 40: %#" PRIx64 "\n", bit40);
    printf("inverted byte: %#x\n", inverted);
    printf("low 3 bits of 0xff: %#x\n", 0xffu & low_bits(3));
    (void)low_bits(32);
    return 0;
}
