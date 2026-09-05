// memory5.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns 0 on success, -1 for a negative size, -2 for a size over 50.
int process(int size)
{
    char *input = NULL;
    char *output = NULL;
    int result = 0;

    if (size < 0) {
        return -1;
    }
    input = malloc(64);
    if (input == NULL) {
        result = -3;
        goto cleanup;
    }
    memset(input, 'x', 63);
    input[63] = '\0';

    if (size > 50) {
        result = -2;
        goto cleanup;
    }
    output = malloc(64);
    if (output == NULL) {
        result = -3;
        goto cleanup;
    }
    memcpy(output, input, (size_t)size);
    output[size] = '\0';

cleanup:
    free(output);
    free(input);
    return result;
}

int main(void)
{
    printf("process(3) = %d\n", process(3));
    printf("process(-1) = %d\n", process(-1));
    printf("process(100) = %d\n", process(100));
    return 0;
}
