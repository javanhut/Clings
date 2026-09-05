// structs5.c
//
// CONCEPT
// `typedef` gives a type a new name. With structs it removes the need to
// write `struct` everywhere:
//
//     typedef struct {
//         double x, y;
//     } vec2;
//
//     vec2 v = {1.0, 2.0};
//
// Small structs like this are passed and returned *by value*, exactly
// like ints; a function `vec2 vec_add(vec2 a, vec2 b)` reads naturally
// and copying 16 bytes is nothing. A *compound literal*, `(vec2){3, 4}`,
// creates a struct value inline, for example as a return value or an
// argument.
//
// Some style guides dislike typedef'd structs (the Linux kernel forbids
// it) because `struct foo` tells the reader it is a struct; others use
// them everywhere. Pick one style per project.
//
// WHEN YOU USE THIS
// Math types (vectors, colors, complex numbers), pairs and small
// results, "handle" types that wrap an int. The by-value style makes
// expression-like code possible: `vec_add(vec_scale(a, 2), b)`.
//
// TASK
// Define the `vec2` typedef and write vec_add, vec_scale, vec_dot and
// vec_len (use sqrt from <math.h>), all by value.
//
// EXPECTED OUTPUT
//     a + b = (4.0, 6.0)
//     2 * a = (2.0, 4.0)
//     a . b = 11.0
//     |b| = 5.0
//     (a + b) scaled by 0.5 = (2.0, 3.0)

#include <math.h>
#include <stdio.h>

// TODO: typedef vec2 with double members x and y.

// TODO: vec2 vec_add(vec2 a, vec2 b);
// TODO: vec2 vec_scale(vec2 v, double k);
// TODO: double vec_dot(vec2 a, vec2 b);
// TODO: double vec_len(vec2 v);

static void print_vec(const char *label, vec2 v)
{
    printf("%s = (%.1f, %.1f)\n", label, v.x, v.y);
}

int main(void)
{
    vec2 a = {1.0, 2.0};
    vec2 b = {3.0, 4.0};

    print_vec("a + b", vec_add(a, b));
    print_vec("2 * a", vec_scale(a, 2.0));
    printf("a . b = %.1f\n", vec_dot(a, b));
    printf("|b| = %.1f\n", vec_len(b));
    print_vec("(a + b) scaled by 0.5", vec_scale(vec_add(a, b), 0.5));
    return 0;
}
