// bits5.c - solution

#include <stdint.h>
#include <stdio.h>

void print_binary8(uint8_t value)
{
    for (int i = 7; i >= 0; i--) {
        putchar(((value >> i) & 1) ? '1' : '0');
    }
}

uint8_t reverse_bits8(uint8_t value)
{
    uint8_t result = 0;

    for (int i = 0; i < 8; i++) {
        result = (uint8_t)((result << 1) | (value & 1));
        value >>= 1;
    }
    return result;
}

int trailing_zeros(uint32_t value)
{
    if (value == 0) {
        return 32;
    }
    int n = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        n++;
    }
    return n;
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
