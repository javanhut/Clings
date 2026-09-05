// strings3.c
//
// CONCEPT
// Modifying a string in place is the C way: no allocation, no copy, the
// caller's buffer is updated. The function takes `char *` (not const,
// because it writes), finds the end with strlen, and works with two
// indices or two pointers moving toward each other.
//
// Careful with the terminator: it stays where it is. Reversing "abc" in
// place swaps a and c, leaves b, and the '\0' at index 3 is untouched.
//
// WHEN YOU USE THIS
// Trimming whitespace, upper-casing, replacing separators, reversing,
// removing characters: all the everyday string cleanup. The alternative,
// building a new string, needs malloc and a free later.
//
// TASK
// Implement `reverse` so that it reverses the string in place. It must
// handle the empty string (length 0) without touching memory.
//
// EXPECTED OUTPUT
//     reversed: sgnilc
//     reversed: a
//     reversed:

#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
    // TODO: reverse the characters of s in place.
    (void)s;
}

int main(void)
{
    char word[] = "clings";
    char one[] = "a";
    char empty[] = "";

    reverse(word);
    printf("reversed: %s\n", word);
    reverse(one);
    printf("reversed: %s\n", one);
    reverse(empty);
    printf("reversed: %s\n", empty);
    return 0;
}
