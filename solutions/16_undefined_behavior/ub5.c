// ub5.c - solution

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void squares(void)
{
    int sq[5];

    for (int i = 0; i < 5; i++) {
        sq[i] = i * i;
    }
    printf("squares: %d %d %d %d %d\n", sq[0], sq[1], sq[2], sq[3], sq[4]);
}

static void doubled(void)
{
    int *v = malloc(3 * sizeof *v);

    if (v == NULL) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        v[i] = i + 1;
    }
    printf("doubled: %d %d %d\n", v[0] * 2, v[1] * 2, v[2] * 2);
    free(v);
}

static uint32_t low_mask(unsigned int bits)
{
    if (bits >= 32) {
        return UINT32_MAX;
    }
    return (1u << bits) - 1;
}

static void copy(void)
{
    const char *src = "sanitize";
    char *dst = malloc(strlen(src) + 1);

    if (dst == NULL) {
        return;
    }
    strcpy(dst, src);
    printf("copy: %s\n", dst);
    free(dst);
}

static size_t length(const char *s)
{
    return s == NULL ? 0 : strlen(s);
}

int main(void)
{
    squares();
    doubled();
    printf("mask: %#x\n", low_mask(32));
    copy();
    printf("length of NULL: %zu\n", length(NULL));
    return 0;
}
