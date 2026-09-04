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
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    default:
        printf("Weekend\n");
        break;
    }
    return 0;
}
