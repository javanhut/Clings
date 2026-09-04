// switch1.c
//
// In a `switch`, execution keeps "falling through" from one `case` into
// the next until it hits a `break`. This program is supposed to print only
// the name of day 3:
//
//     Wednesday
//
// but it prints several lines. Fix it.

#include <stdio.h>

int main(void)
{
    int day = 3;

    switch (day) {
    case 1:
        printf("Monday\n");
    case 2:
        printf("Tuesday\n");
    case 3:
        printf("Wednesday\n");
    case 4:
        printf("Thursday\n");
    case 5:
        printf("Friday\n");
    default:
        printf("Weekend\n");
    }
    return 0;
}
