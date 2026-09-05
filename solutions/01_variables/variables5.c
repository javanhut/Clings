// variables5.c - solution

#include <stdio.h>

int main(void)
{
    int width = 7;
    int height = 3;
    double scale = 1.5;

    int area = width * height;
    int perimeter = 2 * (width + height);
    double scaled = area * scale;
    int tile = 4 * 4;
    int tiles = area / tile;
    int leftover = area % tile;

    printf("Area: %d\n", area);
    printf("Perimeter: %d\n", perimeter);
    printf("Scaled area: %.1f\n", scaled);
    printf("Tiles: %d, leftover: %d\n", tiles, leftover);
    return 0;
}
