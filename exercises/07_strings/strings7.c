// strings7.c
//
// CONCEPT
// strcpy and strcat do not know how big the destination is. If the
// source is longer than the buffer, they keep writing past its end: a
// *buffer overflow*, the bug behind decades of security exploits. The
// classic 1988 Internet worm used exactly this in a `gets` call.
//
// The safe tools:
//     snprintf(buf, sizeof(buf), "%s%s", a, b);
//         never writes more than sizeof(buf) bytes, always terminates,
//         returns the length the full result WOULD have had, so
//         `if (n >= sizeof(buf))` tells you it was truncated.
//     strncpy(dst, src, n)
//         a trap: does NOT terminate when src is n or longer. Avoid.
//     strlcpy / strlcat
//         safe, but BSD/macOS only until C23; not in glibc before 2.38.
//
// The habit: every buffer has a size, and every write into it is bounded
// by that size, either by snprintf or by an explicit check before
// strcpy/strcat/memcpy.
//
// WHEN YOU USE THIS
// Building file paths, log lines, protocol messages, anything assembled
// from pieces of unknown length. Run this file as is and read the
// AddressSanitizer report: "stack-buffer-overflow" with the line number.
//
// TASK
// Rewrite `make_path` with snprintf so it never overflows `out`. When the
// result does not fit, it must return false and leave `out` a valid
// (truncated) string; otherwise true. Do not enlarge the buffer in main.
//
// EXPECTED OUTPUT
//     ok: /home/ada/notes.txt
//     truncated: /home/ada/a-very-lo

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool make_path(char *out, size_t cap, const char *dir, const char *file)
{
    strcpy(out, dir);
    strcat(out, "/");
    strcat(out, file);
    (void)cap;
    return true;
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
