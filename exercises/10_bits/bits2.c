// bits2.c
//
// CONCEPT
// A *bit flag* is one bit of an integer used as a boolean. Define each
// flag as a power of two with a shift (`1u << n`) so they occupy
// different bits, then:
//
//     set:     flags |= FLAG
//     clear:   flags &= ~FLAG
//     toggle:  flags ^= FLAG
//     test:    (flags & FLAG) != 0
//     test all of a set:   (flags & MASK) == MASK
//     test any of a set:   (flags & MASK) != 0
//
// The result of `flags & FLAG` is the flag's value or 0, not 1 or 0. Do
// not compare it with `== 1`; compare with `!= 0` or use `!!` to
// normalize.
//
// WHEN YOU USE THIS
// open() takes flags like O_RDONLY | O_CREAT; window systems, network
// stacks, game entity properties: any set of booleans that must be cheap
// to pass around or store. 32 booleans in 4 bytes, tested in one
// instruction.
//
// TASK
// Write the four flag functions and `describe`, which prints the names
// of the set flags in the order bold, italic, underline separated by
// spaces, or "none".
//
// EXPECTED OUTPUT
//     none
//     bold
//     bold underline
//     bold italic underline
//     italic underline
//     underline
//     has bold+italic: no

#include <stdbool.h>
#include <stdio.h>

enum style {
    STYLE_BOLD = 1u << 0,
    STYLE_ITALIC = 1u << 1,
    STYLE_UNDERLINE = 1u << 2,
};

unsigned int style_set(unsigned int flags, unsigned int flag)
{
    // TODO
    (void)flag;
    return flags;
}

unsigned int style_clear(unsigned int flags, unsigned int flag)
{
    // TODO
    (void)flag;
    return flags;
}

unsigned int style_toggle(unsigned int flags, unsigned int flag)
{
    // TODO
    (void)flag;
    return flags;
}

bool style_has_all(unsigned int flags, unsigned int mask)
{
    // TODO: true when every bit of mask is set in flags.
    (void)flags;
    (void)mask;
    return false;
}

void describe(unsigned int flags)
{
    // TODO
    (void)flags;
    printf("\n");
}

int main(void)
{
    unsigned int s = 0;

    describe(s);
    s = style_set(s, STYLE_BOLD);
    describe(s);
    s = style_set(s, STYLE_UNDERLINE);
    describe(s);
    s = style_toggle(s, STYLE_ITALIC);
    describe(s);
    s = style_clear(s, STYLE_BOLD);
    describe(s);
    s = style_toggle(s, STYLE_ITALIC);
    describe(s);
    printf("has bold+italic: %s\n",
           style_has_all(s, STYLE_BOLD | STYLE_ITALIC) ? "yes" : "no");
    return 0;
}
