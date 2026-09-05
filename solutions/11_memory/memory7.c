// memory7.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns a newly allocated copy of s; the caller frees it.
char *my_strdup(const char *s)
{
    size_t size = strlen(s) + 1;
    char *copy = malloc(size);

    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, size);
    return copy;
}

// Returns a newly allocated string; the caller frees it.
char *join(const char **parts, size_t count, const char *sep)
{
    size_t sep_len = strlen(sep);
    size_t total = 1;

    for (size_t i = 0; i < count; i++) {
        total += strlen(parts[i]);
        if (i + 1 < count) {
            total += sep_len;
        }
    }

    char *out = malloc(total);
    if (out == NULL) {
        return NULL;
    }
    char *p = out;
    for (size_t i = 0; i < count; i++) {
        size_t n = strlen(parts[i]);
        memcpy(p, parts[i], n);
        p += n;
        if (i + 1 < count) {
            memcpy(p, sep, sep_len);
            p += sep_len;
        }
    }
    *p = '\0';
    return out;
}

int main(void)
{
    const char *original = "clings";
    char *copy = my_strdup(original);
    const char *path[] = {"usr", "local", "bin"};
    const char *greek[] = {"alpha", "beta"};

    if (copy == NULL) {
        return 1;
    }
    printf("copy: %s (same memory: %s)\n", copy, copy == original ? "yes" : "no");
    free(copy);

    char *j1 = join(path, 3, "/");
    char *j2 = join(greek, 2, ", ");
    char *j3 = join(path, 0, "/");
    if (j1 == NULL || j2 == NULL || j3 == NULL) {
        return 1;
    }
    printf("joined: %s\n", j1);
    printf("joined: %s\n", j2);
    printf("joined: '%s'\n", j3);
    free(j1);
    free(j2);
    free(j3);
    return 0;
}
