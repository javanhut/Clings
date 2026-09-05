// memory1.c - solution

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count = 5;
    int *squares = malloc(count * sizeof *squares);

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
