// draw.h
//
// This header needs `struct rect`, so it includes shapes.h itself. That
// is the right thing to do: a header should include what it needs and
// not rely on the .c file having included it first. But it means
// shapes.h ends up included twice in macros4.c.

#ifndef DRAW_H
#define DRAW_H

#include "shapes.h"

void draw_rect(struct rect r);

#endif
