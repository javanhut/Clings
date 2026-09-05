// memory6.c - solution

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
    struct grid *g = malloc(sizeof *g);

    if (g == NULL) {
        return NULL;
    }
    g->cells = calloc(rows * cols, sizeof *g->cells);
    if (g->cells == NULL) {
        free(g);
        return NULL;
    }
    g->rows = rows;
    g->cols = cols;
    return g;
}

int *grid_at(struct grid *g, size_t r, size_t c)
{
    return &g->cells[r * g->cols + c];
}

void grid_free(struct grid *g)
{
    if (g == NULL) {
        return;
    }
    free(g->cells);
    free(g);
}

int **matrix_new(size_t rows, size_t cols)
{
    int **m = malloc(rows * sizeof *m);

    if (m == NULL) {
        return NULL;
    }
    for (size_t r = 0; r < rows; r++) {
        m[r] = calloc(cols, sizeof *m[r]);
        if (m[r] == NULL) {
            matrix_free(m, r);
            return NULL;
        }
    }
    return m;
}

void matrix_free(int **m, size_t rows)
{
    if (m == NULL) {
        return;
    }
    for (size_t r = 0; r < rows; r++) {
        free(m[r]);
    }
    free(m);
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
