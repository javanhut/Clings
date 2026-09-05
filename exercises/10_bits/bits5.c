// bits5.c
//
// CONCEPT
// Walking the bits of a value from the top down prints its binary form:
// for i from width-1 to 0, print `(value >> i) & 1`. Reversing the bits
// of a byte builds the result one bit at a time: shift the result left,
// bring in the lowest bit of the input, shift the input right.
//
// "Trailing zeros" (how many 0 bits below the lowest 1) is what memory
// allocators and schedulers use to find the first free slot in a bitmap.
// The naive loop is fine; compilers also offer __builtin_ctz, and C23
// adds stdc_trailing_zeros in <stdbit.h>.
//
// WHEN YOU USE THIS
// Debug output of registers and flags, bitmaps (free-block maps, sets of
// small integers), bit-reversal in FFTs and CRC computation.
//
// TASK
// Write print_binary8 (prints exactly 8 characters, no newline),
// reverse_bits8 and trailing_zeros (return 32 for 0).
//
// EXPECTED OUTPUT
//     0xa5 = 10100101
//     reversed = 10100101
//     0x1e = 00011110
//     reversed = 01111000
//     trailing_zeros(0x1e) = 1
//     trailing_zeros(0x80) = 7
//     trailing_zeros(0) = 32

#include <stdint.h>
#include <stdio.h>

void print_binary8(uint8_t value)
{
    // TODO: print bits 7..0 as '0'/'1' characters.
    (void)value;
}

uint8_t reverse_bits8(uint8_t value)
{
    // TODO
    return value;
}

int trailing_zeros(uint32_t value)
{
    // TODO
    (void)value;
    return -1;
}

int main(void)
{
    uint8_t samples[] = {0xa5, 0x1e};

    for (size_t i = 0; i < 2; i++) {
        printf("%#x = ", samples[i]);
        print_binary8(samples[i]);
        printf("\nreversed = ");
        print_binary8(reverse_bits8(samples[i]));
        printf("\n");
    }
    printf("trailing_zeros(0x1e) = %d\n", trailing_zeros(0x1e));
    printf("trailing_zeros(0x80) = %d\n", trailing_zeros(0x80));
    printf("trailing_zeros(0) = %d\n", trailing_zeros(0));
    return 0;
}
