// switch2.c
//
// CONCEPT
// Fallthrough is a feature when several values share one action: stack the
// case labels with nothing between them.
//
//     switch (c) {
//     case 'a': case 'e': case 'i': case 'o': case 'u':
//         return true;
//     default:
//         return false;
//     }
//
// A `return` inside a case leaves the whole function, so no `break` is
// needed after it. Modern compilers warn about *accidental* fallthrough
// (a case with statements that runs into the next one) with
// -Wimplicit-fallthrough; C23 adds `[[fallthrough]];` to mark the
// intentional ones.
//
// WHEN YOU USE THIS
// Grouping: months with 31 days, characters that are whitespace, opcodes
// that share an implementation. It replaces a long `||` chain with a table
// the eye can scan.
//
// TASK
// Write `days_in_month(month, leap)` with a switch: 31 for months
// 1,3,5,7,8,10,12; 30 for 4,6,9,11; February has 28 days, or 29 when
// `leap` is true; any other month returns -1.
//
// EXPECTED OUTPUT
//     month 1: 31 days
//     month 2: 28 days
//     month 2 (leap): 29 days
//     month 4: 30 days
//     month 12: 31 days
//     month 13: -1 days

#include <stdbool.h>
#include <stdio.h>

int days_in_month(int month, bool leap)
{
    // TODO: one switch, grouped cases.
    (void)month;
    (void)leap;
    return 0;
}

int main(void)
{
    printf("month 1: %d days\n", days_in_month(1, false));
    printf("month 2: %d days\n", days_in_month(2, false));
    printf("month 2 (leap): %d days\n", days_in_month(2, true));
    printf("month 4: %d days\n", days_in_month(4, false));
    printf("month 12: %d days\n", days_in_month(12, false));
    printf("month 13: %d days\n", days_in_month(13, false));
    return 0;
}
