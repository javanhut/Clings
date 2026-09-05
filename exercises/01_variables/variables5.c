// variables5.c
//
// CONCEPT
// Arithmetic in C follows the types of the operands, not what you meant.
// `int / int` is integer division (7 / 2 is 3). `int * double` promotes the
// int to double and gives a double. An assignment converts the result to
// the type of the target, silently truncating if needed.
//
// The compound assignment operators `+=`, `-=`, `*=`, `/=`, `%=` update a
// variable in place: `total += x` is `total = total + x`. `%` is the
// remainder (modulo) operator and only works on integers.
//
// WHEN YOU USE THIS
// Any calculation. Choosing the type of each intermediate value is part of
// writing correct C: a percentage computed as `done / total * 100` with ints
// is always 0 or 100. Decide up front which values are counts (int) and
// which are measurements (double), and convert deliberately where they meet.
//
// TASK
// Write the body of main. Declare variables with the right types for a
// rectangle 7 wide and 3 high, a scale factor of 1.5, and compute:
//   - area (an integer), perimeter (an integer),
//   - the scaled area, which is area * scale (a double),
//   - how many full 4x4 tiles fit into the area, and how many square units
//     are left over (integer division and remainder).
// Print them as shown.
//
// EXPECTED OUTPUT
//     Area: 21
//     Perimeter: 20
//     Scaled area: 31.5
//     Tiles: 1, leftover: 5

#include <stdio.h>

int main(void)
{
    // TODO: declare width, height, scale and compute the values above.

    return 0;
}
