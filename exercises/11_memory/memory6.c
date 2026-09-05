// memory6.c
//
// CONCEPT
// `calloc(count, size)` allocates count * size bytes and zeroes them; it
// also checks that the multiplication does not overflow, which
// `malloc(count * size)` does not. Use it whenever you want zeroed
// memory (counters, tables, matrices).
//
// A 2D array whose dimensions are only known at run time is not a
// `int m[rows][cols]`; that would be a VLA on the stack, dangerous for
// big sizes. Two heap layouts:
//
//   1. One flat block of rows * cols elements, indexed by hand:
//          m[r * cols + c]
//      One allocation, one free, contiguous (cache-friendly). Preferred.
//   2. An array of row pointers, each row allocated separately:
//          int **m = malloc(rows * sizeof *m);
//          m[r] = malloc(cols * sizeof *m[r]);   // for each r
//      Allows `m[r][c]` syntax and ragged rows, but costs rows + 1
//      allocations, and freeing must undo all of them.
//
// <string.h> also gives you memset (fill bytes), memcpy (copy bytes,
// regions must not overlap) and memmove (copy, overlap allowed). They
// take `void *` and sizes in bytes.
//
// WHEN YOU USE THIS
// Grids, images, matrices, tables sized by input. Knowing both layouts
// lets you read other people's code; writing new code, use the flat one.
//
// TASK
// Write `grid_new` (flat layout, zeroed, using calloc), `grid_at`
// (returns a pointer to the element so it can be read *and* written),
// and `grid_free`. Then `matrix_new` / `matrix_free` for the
// pointer-to-rows layout; matrix_new must not leak if a row allocation
// fails (free what was allocated so far and return NULL).
//
// EXPECTED OUTPUT
//     grid 3x4:
//     0 0 0 0
//     0 0 7 0
//     0 0 0 0
//     matrix 2x3:
//     0 1 2
//     10 11 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grid {
    int *cells;
    size_t rows;
    size_t cols;
};

// matrix_new calls matrix_free on failure, so it needs the prototype.
void matrix_free(int **m, size_t rows);

struct grid *grid_new(size_t rows, size_t cols)
{
    // TODO: allocate the struct and rows * cols zeroed ints.
    (void)rows;
    (void)cols;
    return NULL;
}

int *grid_at(struct grid *g, size_t r, size_t c)
{
    // TODO
    (void)g;
    (void)r;
    (void)c;
    return NULL;
}

void grid_free(struct grid *g)
{
    // TODO
    (void)g;
}

int **matrix_new(size_t rows, size_t cols)
{
    // TODO: array of row pointers, each row zeroed.
    (void)rows;
    (void)cols;
    return NULL;
}

void matrix_free(int **m, size_t rows)
{
    // TODO
    (void)m;
    (void)rows;
}

int main(void)
{
    struct grid *g = grid_new(3, 4);
    if (g == NULL) {
        return 1;
    }
    *grid_at(g, 1, 2) = 7;
    printf("grid %zux%zu:\n", g->rows, g->cols);
    for (size_t r = 0; r < g->rows; r++) {
        for (size_t c = 0; c < g->cols; c++) {
            printf("%s%d", c > 0 ? " " : "", *grid_at(g, r, c));
        }
        printf("\n");
    }
    grid_free(g);

    int **m = matrix_new(2, 3);
    if (m == NULL) {
        return 1;
    }
    for (size_t r = 0; r < 2; r++) {
        for (size_t c = 0; c < 3; c++) {
            m[r][c] = (int)(r * 10 + c);
        }
    }
    printf("matrix 2x3:\n");
    for (size_t r = 0; r < 2; r++) {
        printf("%d %d %d\n", m[r][0], m[r][1], m[r][2]);
    }
    matrix_free(m, 2);
    return 0;
}
