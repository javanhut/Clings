// intro2.c
//
// CONCEPT
// `printf` prints exactly what you give it. Unlike `println` in other
// languages it does not add a line break: if you want one, you write `\n`
// inside the string. `\n` is an *escape sequence*: a backslash followed by
// a letter that stands for a character you cannot easily type. Others you
// will meet are `\t` (tab), `\"` (a literal double quote inside a string),
// `\\` (a literal backslash) and `\0` (the zero byte that ends every C
// string, more on that in the strings section).
//
// WHEN YOU USE THIS
// Every time you print. Output that is later read by another program (a
// shell script, a test harness such as Clings) depends on newlines being
// exactly where they should be. Also, the C library *buffers* output: text
// without a trailing newline may not appear on the screen until the program
// ends, which confuses people debugging with printf.
//
// TASK
// The program should print two lines but prints them as one. Fix it.
//
// EXPECTED OUTPUT
//     I am
//     learning C

#include <stdio.h>

int main(void)
{
    printf("I am");
    printf("learning C");
    return 0;
}
