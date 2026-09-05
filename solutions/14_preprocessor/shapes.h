// shapes.h - solution: with an include guard.

#ifndef SHAPES_H
#define SHAPES_H

struct rect {
    int width;
    int height;
};

int rect_area(struct rect r);

#endif
