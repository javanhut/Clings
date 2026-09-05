// ub4.c
//
// CONCEPT
// Every type has an *alignment*: an int wants an address divisible by
// 4, a double by 8. Reading an int through a pointer to an odd address
// is undefined; x86 tolerates it (slowly), ARM and others fault, and
// the sanitizer reports "misaligned address" everywhere. The way to get
// a misaligned pointer is casting: `(int *)(buffer + 1)`.
//
// The same cast has a second problem, *strict aliasing*: the compiler
// may assume an `int *` and a `char *` point to different objects, and
// reorder accesses accordingly. So "reinterpret these bytes as an int"
// via a pointer cast is doubly undefined.
//
// The one blessed way to reinterpret bytes is memcpy:
//
//     int value;
//     memcpy(&value, buffer + 1, sizeof value);   // any alignment, no aliasing
//
// The compiler turns that into a single load where the hardware allows
// it; you lose nothing. (Type-punning through a union is the other
// accepted way in C, but memcpy reads as intent and works in C++ too.)
//
// WHEN YOU USE THIS
// Parsing binary formats and network packets: fields sit at arbitrary
// byte offsets in a char buffer. Every deserializer is built on
// memcpy-from-offset, plus byte-order conversion (ntohl, or shifts
// like bits3) when the format is big-endian.
//
// TASK
// `read_u32_at` casts into the middle of a byte buffer. Rewrite it with
// memcpy. Then write `read_u16_be`, which reads a 16-bit big-endian
// value (most significant byte first) at an offset without any casting
// at all, using shifts on the individual bytes.
//
// EXPECTED OUTPUT
//     u32 at 1: 0x4030201
//     u16 be at 5: 0xabcd
//     u16 be at 0: 0x1

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t read_u32_at(const unsigned char *buf, size_t offset)
{
    return *(const uint32_t *)(buf + offset);
}

uint16_t read_u16_be(const unsigned char *buf, size_t offset)
{
    // TODO: no pointer casts; combine buf[offset] and buf[offset + 1].
    (void)buf;
    (void)offset;
    return 0;
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
