// structs2.c - solution

#include <stdio.h>

struct point {
    int x;
    int y;
};

void move(struct point *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

int main(void)
{
    struct point pt = {1, 1};

    move(&pt, 2, 3);
    printf("Point moved to (%d, %d)\n", pt.x, pt.y);
    return 0;
}
