// io5.c
//
// CONCEPT
// Files in C go through a `FILE *`, an opaque handle from <stdio.h>:
//
//     FILE *f = fopen("data.txt", "w");    // "r" read, "w" write/truncate,
//     if (f == NULL) { /* check errno */ } // "a" append, add "b" for binary
//     fprintf(f, "%d\n", 42);              // same formatting as printf
//     fclose(f);                           // flushes buffers, releases the handle
//
// Reading uses fgets(line, size, f) and fscanf(f, ...) exactly like
// stdin, because stdin, stdout and stderr *are* FILE pointers. Output is
// buffered: it may sit in memory until fclose or fflush; forgetting to
// fclose a file you wrote can lose the tail of it. Every fopen needs an
// fclose, like malloc needs free.
//
// Other pieces: `fread`/`fwrite` move raw bytes; `fseek`/`ftell` move
// the position; `remove(path)` deletes a file; `feof` tells you *after*
// a read failed whether it was end-of-file or an error, so testing feof
// in a loop condition is a classic bug (the last line is processed
// twice). Loop on the read function's return value instead.
//
// WHEN YOU USE THIS
// Config files, logs, save games, data import/export. Small programs
// are often "read a file, compute, write a file".
//
// TASK
// Write `write_numbers`, which writes the numbers 1..count one per line
// to `path`, and `sum_file`, which reads the file back line by line and
// returns the sum (-1 if the file cannot be opened). Both must fclose on
// every path. main creates the file, sums it, deletes it, and shows what
// happens when the file is gone.
//
// EXPECTED OUTPUT
//     wrote 10 numbers
//     sum: 55
//     after remove: -1

#include <stdio.h>
#include <stdlib.h>

#define PATH "io5_numbers.tmp"

int write_numbers(const char *path, int count)
{
    // TODO: return count on success, -1 if the file cannot be opened.
    (void)path;
    (void)count;
    return -1;
}

long sum_file(const char *path)
{
    // TODO
    (void)path;
    return -1;
}

int main(void)
{
    int written = write_numbers(PATH, 10);
    if (written < 0) {
        fprintf(stderr, "cannot write %s\n", PATH);
        return 1;
    }
    printf("wrote %d numbers\n", written);
    printf("sum: %ld\n", sum_file(PATH));
    remove(PATH);
    printf("after remove: %ld\n", sum_file(PATH));
    return 0;
}
