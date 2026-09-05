// types3.c
//
// CONCEPT
// Every integer type has a fixed range. An `unsigned char` holds 0..255;
// arithmetic that leaves the range *wraps around* modulo 256, so 250 + 10
// is 4. For unsigned types this wrapping is well defined and sometimes
// wanted (checksums, hash functions, timers). For *signed* types, going
// past the range is undefined behavior; the undefined-behavior section
// comes back to that.
//
// The ranges are in <limits.h>: CHAR_MAX, INT_MAX, INT_MIN, UINT_MAX,
// LONG_MAX. Never hardcode 2147483647; write INT_MAX.
//
// WHEN YOU USE THIS
// Choosing a type is choosing a range. Counting bytes in a file in an int
// breaks at 2 GiB. Storing a Unix timestamp in a 32-bit int breaks in 2038.
// A "small" type is only a good idea when you have millions of them.
//
// TASK
// Pick a type for `value` that can hold the result, and print INT_MAX from
// <limits.h> on the second line.
//
// EXPECTED OUTPUT
//     value is 260
//     an int goes up to 2147483647

#include <stdio.h>

int main(void)
{
    unsigned char value = 250;

    value = value + 10;
    printf("value is %d\n", value);
    printf("an int goes up to %d\n", ???);
    return 0;
}
