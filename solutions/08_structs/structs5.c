// structs5.c - solution

#include <math.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} vec2;

vec2 vec_add(vec2 a, vec2 b)
{
    return (vec2){a.x + b.x, a.y + b.y};
}

vec2 vec_scale(vec2 v, double k)
{
    return (vec2){v.x * k, v.y * k};
}

double vec_dot(vec2 a, vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

double vec_len(vec2 v)
{
    return sqrt(vec_dot(v, v));
}

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
