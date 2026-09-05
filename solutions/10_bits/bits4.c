// bits4.c - solution

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// Returns a mask with the lowest `n` bits set, for n in 0..32.
uint32_t low_bits(unsigned int n)
{
    if (n >= 32) {
        return UINT32_MAX;
    }
    return (1u << n) - 1;
}

int main(void)
{
    unsigned int top = 1u << 31;
    uint64_t bit40 = (uint64_t)1 << 40;
    uint8_t byte = 0x0f;
    uint8_t inverted = (uint8_t)~byte;

    printf("top bit: %#x\n", top);
    printf("bit 40: %#" PRIx64 "\n", bit40);
    printf("inverted byte: %#x\n", inverted);
    printf("low 3 bits of 0xff: %#x\n", 0xffu & low_bits(3));
    (void)low_bits(32);
    return 0;
}
