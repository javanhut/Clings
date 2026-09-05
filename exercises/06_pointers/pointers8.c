// pointers8.c
//
// CONCEPT
// A pointer is a variable, so it has an address too, and a function can
// receive a pointer *to a pointer* in order to change which thing the
// caller's pointer points at. `char **cursor` is "pointer to pointer to
// char"; `*cursor` is the caller's `char *`; `**cursor` is the character
// it points at.
//
//     void skip_spaces(const char **cursor)
//     {
//         while (**cursor == ' ') {
//             (*cursor)++;        // advance the CALLER's pointer
//         }
//     }
//
// The parentheses matter: `*cursor++` would advance `cursor` itself (the
// local copy) and dereference the old value. Precedence: postfix ++ binds
// tighter than prefix *.
//
// You have already met a pointer to pointer: `char *argv[]` in main is
// `char **argv`, an array of strings. And functions that allocate
// something for the caller often take `T **out`.
//
// WHEN YOU USE THIS
// Parsers that advance a shared cursor, functions that hand back an
// allocated object, linked-list code that inserts at the head (it must
// change the caller's head pointer), arrays of strings.
//
// TASK
// Write `skip_spaces` as above and `take_word`, which copies the
// characters up to the next space or end of string into `out` (at most
// `cap - 1` of them, then a terminating '\0') and advances the caller's
// cursor past the word. Then `choose`, which makes the caller's `int *`
// point at whichever of a and b is larger.
//
// EXPECTED OUTPUT
//     word: 'hello'
//     word: 'pointer'
//     word: 'world'
//     rest: ''
//     larger is 9

#include <stddef.h>
#include <stdio.h>

void skip_spaces(const char **cursor)
{
    // TODO
    (void)cursor;
}

void take_word(const char **cursor, char *out, size_t cap)
{
    // TODO
    (void)cursor;
    (void)out;
    (void)cap;
}

void choose(int **out, int *a, int *b)
{
    // TODO: *out becomes a or b, whichever points at the larger value.
    (void)out;
    (void)a;
    (void)b;
}

int main(void)
{
    const char *text = "  hello   pointer world";
    const char *cursor = text;
    char word[16];

    for (int i = 0; i < 3; i++) {
        skip_spaces(&cursor);
        take_word(&cursor, word, sizeof(word));
        printf("word: '%s'\n", word);
    }
    skip_spaces(&cursor);
    printf("rest: '%s'\n", cursor);

    int a = 4;
    int b = 9;
    int *larger = NULL;
    choose(&larger, &a, &b);
    printf("larger is %d\n", *larger);
    return 0;
}
