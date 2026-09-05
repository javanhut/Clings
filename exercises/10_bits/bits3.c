// bits3.c
//
// CONCEPT
// Shifts and masks let you pack several small values into one integer
// and pull them out again:
//
//     pack:    (r << 16) | (g << 8) | b          three bytes in 24 bits
//     unpack:  (color >> 8) & 0xFF               the middle byte
//
// `& 0xFF` keeps the low 8 bits and clears the rest; `>> 8` moves the
// next byte down into that position. Together they are "extract field".
//
// A few one-liners every C programmer eventually learns:
//     x & (x - 1)        clears the lowest set bit
//                        (so x is a power of two iff x != 0 and this is 0)
//     x & -x             isolates the lowest set bit (on unsigned)
//     popcount           count set bits: loop clearing the lowest one
//
// WHEN YOU USE THIS
// Pixel formats (RGB in a uint32_t), instruction decoding, IP addresses
// (four bytes in a uint32_t), compact keys, hashing, memory allocators
// (power-of-two size classes).
//
// TASK
// Write pack_rgb, get_byte (byte 0 is the lowest), popcount and
// is_power_of_two.
//
// EXPECTED OUTPUT
//     packed = 0x11aa33
//     byte 0 = 0x33
//     byte 1 = 0xaa
//     byte 2 = 0x11
//     popcount(0) = 0
//     popcount(0xff) = 8
//     popcount(0x11aa33) = 10
//     is_power_of_two(64) = yes
//     is_power_of_two(96) = no
//     is_power_of_two(0) = no

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint32_t pack_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    // TODO
    (void)r;
    (void)g;
    (void)b;
    return 0;
}

uint8_t get_byte(uint32_t value, unsigned int index)
{
    // TODO: index 0 is the least significant byte.
    (void)value;
    (void)index;
    return 0;
}

int popcount(uint32_t value)
{
    // TODO
    (void)value;
    return -1;
}

bool is_power_of_two(uint32_t value)
{
    // TODO
    (void)value;
    return false;
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
