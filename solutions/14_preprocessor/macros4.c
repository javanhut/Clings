// macros4.c - solution (the fix is in shapes.h next to this file)
//
// CONCEPT
// A C program of any size is several .c files ("translation units"),
// each compiled separately, then linked. They share declarations through
// header files: a .h file holds struct definitions, prototypes and
// constants, and every .c file that needs them does `#include "name.h"`.
// The .c file with the definitions includes its own header too, so the
// compiler checks that declarations and definitions agree.
//
// Because headers include other headers, the same header can be pulled
// in twice, and a second `struct rect { ... }` is a compile error. An
// *include guard* makes a header idempotent:
//
//     #ifndef SHAPES_H
//     #define SHAPES_H
//     ... contents ...
//     #endif
//
// The first inclusion defines SHAPES_H; the second sees it defined and
// skips everything. `#pragma once` at the top does the same on every
// compiler you will meet, with less ceremony; both are common.
//
// This exercise has four files. Clings compiles macros4.c together with
// draw.c; both include the headers next to them.
//
// WHEN YOU USE THIS
// Every header you ever write gets a guard, first thing. Every module
// gets a header for its public interface. Learn to read linker errors
// ("undefined reference to `rect_area'") as "some .c file with that
// definition was not compiled in".
//
// TASK
// Add an include guard to shapes.h (the file next to this one). Nothing
// in this .c file needs to change; edit the header and save, or press
// `r` to re-check.
//
// EXPECTED OUTPUT
//     area: 6
//     ###
//     ###

#include <stdio.h>

#include "draw.h"
#include "shapes.h"

int main(void)
{
    struct rect r = {3, 2};

    printf("area: %d\n", rect_area(r));
    draw_rect(r);
    return 0;
}
