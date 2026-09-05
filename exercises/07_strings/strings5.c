// strings5.c
//
// CONCEPT
// There are two very different ways to "have a string":
//
//     char *p = "hello";    // p points at a string LITERAL
//     char a[] = "hello";   // a is an ARRAY initialized with a copy
//
// A string literal lives in read-only memory for the whole program.
// Writing to it (`p[0] = 'H'`) is undefined behavior and crashes on every
// modern system. The array is yours: it is on the stack, writable, and
// sized to fit (6 bytes here). Declare pointers to literals as
// `const char *` so the compiler stops you from writing through them.
//
// A related trap: `char *s = "hi"; s = "there";` is fine (the pointer is
// repointed), while `char a[] = "hi"; a = "there";` does not compile
// (arrays cannot be assigned); you would use strcpy, with a big enough
// array.
//
// WHEN YOU USE THIS
// Use `const char *` for text you only read (messages, names, keys); use
// a `char buf[N]` when you need to build or edit text. Knowing which one
// you hold is the difference between a working program and a crash.
//
// TASK
// `capitalize` is called on a string literal and crashes. Fix main so the
// function has a writable copy to work on. Also mark `greeting` in
// `print_twice` as const, since it is only read.
//
// EXPECTED OUTPUT
//     Hello
//     Hello

#include <ctype.h>
#include <stdio.h>

void capitalize(char *s)
{
    if (s[0] != '\0') {
        s[0] = (char)toupper((unsigned char)s[0]);
    }
}

void print_twice(char *greeting)
{
    printf("%s\n%s\n", greeting, greeting);
}

int main(void)
{
    char *word = "hello";

    capitalize(word);
    print_twice(word);
    return 0;
}
