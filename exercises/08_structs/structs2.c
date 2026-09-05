// structs2.c
//
// CONCEPT
// Functions usually receive a *pointer* to a struct rather than the
// struct itself: passing by value copies every member, and a copy cannot
// be modified for the caller. Through a pointer, members are accessed
// with `->`:
//
//     p->x        is shorthand for      (*p).x
//
// The parentheses in the long form are required, because `.` binds
// tighter than `*`; `*p.x` would mean `*(p.x)`. Nobody writes the long
// form; `->` is the idiom.
//
// WHEN YOU USE THIS
// Nearly every function that takes a struct takes a pointer to it:
// `void point_move(struct point *p, int dx, int dy)`. The first
// parameter being a pointer to "the object" is the C equivalent of
// `this`/`self`. Read-only functions take `const struct point *`.
//
// TASK
// Fix `move` so it modifies the caller's point.
//
// EXPECTED OUTPUT
//     Point moved to (3, 4)

#include <stdio.h>

struct point {
    int x;
    int y;
};

void move(struct point *p, int dx, int dy)
{
    p.x += dx;
    p.y += dy;
}

int main(void)
{
    struct point pt = {1, 1};

    move(&pt, 2, 3);
    printf("Point moved to (%d, %d)\n", pt.x, pt.y);
    return 0;
}
