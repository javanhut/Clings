// bits2.c - solution

#include <stdbool.h>
#include <stdio.h>

enum style {
    STYLE_BOLD = 1u << 0,
    STYLE_ITALIC = 1u << 1,
    STYLE_UNDERLINE = 1u << 2,
};

unsigned int style_set(unsigned int flags, unsigned int flag)
{
    return flags | flag;
}

unsigned int style_clear(unsigned int flags, unsigned int flag)
{
    return flags & ~flag;
}

unsigned int style_toggle(unsigned int flags, unsigned int flag)
{
    return flags ^ flag;
}

bool style_has_all(unsigned int flags, unsigned int mask)
{
    return (flags & mask) == mask;
}

void describe(unsigned int flags)
{
    if (flags == 0) {
        printf("none\n");
        return;
    }
    const char *sep = "";
    if (flags & STYLE_BOLD) {
        printf("%sbold", sep);
        sep = " ";
    }
    if (flags & STYLE_ITALIC) {
        printf("%sitalic", sep);
        sep = " ";
    }
    if (flags & STYLE_UNDERLINE) {
        printf("%sunderline", sep);
    }
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
