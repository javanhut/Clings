// structs2.c
//
// When you have a *pointer* to a struct, you access its members with `->`
// instead of `.` (`p->x` is shorthand for `(*p).x`). Fix `move` so the
// program prints:
//
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
