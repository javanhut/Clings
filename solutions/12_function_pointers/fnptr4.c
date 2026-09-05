// fnptr4.c - solution

#include <stdio.h>
#include <string.h>

struct command {
    const char *name;
    int (*run)(int, int);
};

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

static int mul(int a, int b)
{
    return a * b;
}

static int div_(int a, int b)
{
    if (b == 0) {
        printf("error: division by zero\n");
        return 0;
    }
    return a / b;
}

static const struct command commands[] = {
    {"add", add},
    {"sub", sub},
    {"mul", mul},
    {"div", div_},
};

void run(const char *name, int a, int b)
{
    size_t count = sizeof commands / sizeof commands[0];

    for (size_t i = 0; i < count; i++) {
        if (strcmp(commands[i].name, name) == 0) {
            printf("%s %d %d = %d\n", name, a, b, commands[i].run(a, b));
            return;
        }
    }
    printf("unknown command: %s\n", name);
}

int main(void)
{
    run("add", 7, 3);
    run("sub", 7, 3);
    run("mul", 7, 3);
    run("div", 7, 3);
    run("div", 7, 0);
    run("pow", 7, 3);
    return 0;
}
