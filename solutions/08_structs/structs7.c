// structs7.c - solution

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
    switch (v->kind) {
    case V_INT:
        printf("int %d\n", v->as.i);
        break;
    case V_DOUBLE:
        printf("double %.2f\n", v->as.d);
        break;
    case V_STRING:
        printf("string %s\n", v->as.s);
        break;
    }
}

double value_as_double(const struct value *v)
{
    switch (v->kind) {
    case V_INT:
        return v->as.i;
    case V_DOUBLE:
        return v->as.d;
    case V_STRING:
        return 0.0;
    }
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
