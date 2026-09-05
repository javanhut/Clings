// draw.c - support file for macros4; nothing to change here.

#include <stdio.h>

#include "draw.h"

int rect_area(struct rect r)
{
    return r.width * r.height;
}

void draw_rect(struct rect r)
{
    for (int y = 0; y < r.height; y++) {
        for (int x = 0; x < r.width; x++) {
            putchar('#');
        }
        putchar('\n');
    }
}
