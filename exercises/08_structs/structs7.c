// structs7.c
//
// CONCEPT
// A `union` looks like a struct but all its members share the *same*
// memory: it is as big as its largest member, and writing one member
// overwrites the others. On its own that is dangerous (reading a member
// other than the one last written is only well-defined for reinterpreting
// bytes). Paired with a *tag* that records which member is valid, it
// becomes the C version of a variant / sum type:
//
//     struct value {
//         enum { V_INT, V_DOUBLE, V_STRING } kind;   // the tag
//         union {
//             int i;
//             double d;
//             const char *s;
//         } as;                                       // the payload
//     };
//
// Code that handles a value switches on the tag and reads only the
// matching member. Every JSON library, every interpreter's value type and
// every event queue in C is built like this.
//
// Also worth knowing: the compiler *pads* structs so each member sits at
// an address that is a multiple of its size (an int at a multiple of 4).
// `struct { char c; int i; }` is 8 bytes, not 5. Ordering members from
// largest to smallest minimizes padding. sizeof tells the truth; never
// assume.
//
// WHEN YOU USE THIS
// Tagged unions: interpreters, parsers, message passing, anything
// "one of several kinds". Padding: file formats, network packets,
// memory-tight tables.
//
// TASK
// Write `value_print`, which prints "int 42", "double 2.50" or
// "string hello" depending on the tag, and `value_as_double`, which
// converts int and double values to double and returns 0.0 for strings.
// The padding demo in main is complete; read it and predict the numbers
// before running.
//
// EXPECTED OUTPUT
//     int 42
//     double 2.50
//     string hello
//     sum of numeric values: 44.5
//     sizeof(struct padded) = 12
//     sizeof(struct packed) = 8

#include <stdio.h>

enum kind {
    V_INT,
    V_DOUBLE,
    V_STRING,
};

struct value {
    enum kind kind;
    union {
        int i;
        double d;
        const char *s;
    } as;
};

struct padded {
    char a;
    int b;
    char c;
};

struct packed {
    int b;
    char a;
    char c;
};

void value_print(const struct value *v)
{
    // TODO
    (void)v;
}

double value_as_double(const struct value *v)
{
    // TODO
    (void)v;
    return 0.0;
}

int main(void)
{
    struct value values[] = {
        {.kind = V_INT, .as.i = 42},
        {.kind = V_DOUBLE, .as.d = 2.5},
        {.kind = V_STRING, .as.s = "hello"},
    };
    double sum = 0.0;

    for (size_t i = 0; i < 3; i++) {
        value_print(&values[i]);
        sum += value_as_double(&values[i]);
    }
    printf("sum of numeric values: %.1f\n", sum);
    printf("sizeof(struct padded) = %zu\n", sizeof(struct padded));
    printf("sizeof(struct packed) = %zu\n", sizeof(struct packed));
    return 0;
}
