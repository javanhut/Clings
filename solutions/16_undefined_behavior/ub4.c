// ub4.c - solution

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t read_u32_at(const unsigned char *buf, size_t offset)
{
    uint32_t value;

    memcpy(&value, buf + offset, sizeof value);
    return value;
}

uint16_t read_u16_be(const unsigned char *buf, size_t offset)
{
    return (uint16_t)(((unsigned int)buf[offset] << 8) | buf[offset + 1]);
}

int main(void)
{
    // Byte 0 is a header; the u32 starts at byte 1 (misaligned on purpose).
    unsigned char packet[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0xab, 0xcd};

    printf("u32 at 1: %#x\n", read_u32_at(packet, 1));
    printf("u16 be at 5: %#x\n", read_u16_be(packet, 5));
    printf("u16 be at 0: %#x\n", read_u16_be(packet, 0));
    return 0;
}
