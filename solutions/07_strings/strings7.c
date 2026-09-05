// strings7.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool make_path(char *out, size_t cap, const char *dir, const char *file)
{
    int n = snprintf(out, cap, "%s/%s", dir, file);

    return n >= 0 && (size_t)n < cap;
}

int main(void)
{
    char path[20];

    if (make_path(path, sizeof(path), "/home/ada", "notes.txt")) {
        printf("ok: %s\n", path);
    } else {
        printf("truncated: %s\n", path);
    }
    if (make_path(path, sizeof(path), "/home/ada", "a-very-long-file-name.txt")) {
        printf("ok: %s\n", path);
    } else {
        printf("truncated: %s\n", path);
    }
    return 0;
}
