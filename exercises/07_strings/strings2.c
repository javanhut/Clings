// strings2.c
//
// CONCEPT
// A string is an array, and an array in an expression is a pointer to
// its first element. So `answer == "yes"` compares two *addresses*: the
// array in main and a string literal stored elsewhere. They are never
// equal, whatever the contents. Likewise `s1 = s2` does not copy a string,
// it copies a pointer (and does not even compile for arrays).
//
// <string.h> has the real operations:
//     strcmp(a, b)      0 when equal, negative when a sorts before b,
//                       positive after; use `strcmp(a, b) == 0` for "equal"
//     strncmp(a, b, n)  compare at most n characters
//     strcpy(dst, src)  copy (dst must have room: strings7)
//     strcat(dst, src)  append
//     strchr(s, c)      pointer to the first c in s, or NULL
//     strstr(s, sub)    pointer to the first occurrence of sub, or NULL
//
// WHEN YOU USE THIS
// Any comparison of user input, command names, file extensions, keys.
// The `== 0` in `strcmp(a, b) == 0` reads backwards ("not different") and
// people forget it constantly; some code bases wrap it in a macro
// `STREQ(a, b)`.
//
// TASK
// Use the right function to compare contents.
//
// EXPECTED OUTPUT
//     Confirmed
//     "apple" sorts before "banana"

#include <stdio.h>
#include <string.h>

int main(void)
{
    char answer[] = "yes";

    if (answer == "yes") {
        printf("Confirmed\n");
    } else {
        printf("Denied\n");
    }
    if (??? < 0) {
        printf("\"apple\" sorts before \"banana\"\n");
    }
    return 0;
}
