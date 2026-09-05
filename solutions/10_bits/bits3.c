// bits3.c - solution

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint32_t pack_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint8_t get_byte(uint32_t value, unsigned int index)
{
    return (uint8_t)((value >> (8 * index)) & 0xFF);
}

int popcount(uint32_t value)
{
    int count = 0;

    while (value != 0) {
        value &= value - 1;
        count++;
    }
    return count;
}

bool is_power_of_two(uint32_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

int main(void)
{
    uint32_t color = pack_rgb(0x11, 0xaa, 0x33);

    printf("packed = %#x\n", color);
    for (unsigned int i = 0; i < 3; i++) {
        printf("byte %u = %#x\n", i, get_byte(color, i));
    }
    printf("popcount(0) = %d\n", popcount(0));
    printf("popcount(0xff) = %d\n", popcount(0xff));
    printf("popcount(0x11aa33) = %d\n", popcount(0x11aa33));
    printf("is_power_of_two(64) = %s\n", is_power_of_two(64) ? "yes" : "no");
    printf("is_power_of_two(96) = %s\n", is_power_of_two(96) ? "yes" : "no");
    printf("is_power_of_two(0) = %s\n", is_power_of_two(0) ? "yes" : "no");
    return 0;
}
