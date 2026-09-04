// memory1.c
//
// `malloc` asks for a block of memory of a given number of *bytes* and
// returns a pointer to it (or NULL if it fails). When you are done, you
// give the memory back with `free`.
//
// Replace `???` with the right number of bytes for `count` ints, and free
// the memory at the end. Expected output:
//
//     Squares: 0 1 4 9 16

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count = 5;
    int *squares = malloc(count * sizeof(int));

    if (squares == NULL) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        squares[i] = i * i;
    }

    printf("Squares:");
    for (int i = 0; i < count; i++) {
        printf(" %d", squares[i]);
    }
    printf("\n");

    free(squares);
    return 0;
}
