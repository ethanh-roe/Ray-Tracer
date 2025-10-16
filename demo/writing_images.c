#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define X 1024
#define Y 768

#define R 0
#define G 1
#define B 2

uint8_t raster[Y][X][3];

int main(int argc, char *argv[]) {
    int x, y;
    FILE *f;

    for(y = 0; y < Y; y++){
        for(x = 0; x < X; x++){
            raster[y][x][R] = (x * 255) / X;
            raster[y][x][G] = (y * 255) / Y;
            raster[y][x][B] = 255-((y * 255) / Y);
        }
    }

    f = fopen("gradient.ppm", "wb"); // b is ignored in non-Windows environments
                                     // In windows, "binary mode",
                                     // suppressed carriage return after \n

    fprintf(f, "P6\n%d\n%d\n255\n", X, Y);
    fwrite(raster, 3 * sizeof (uint8_t), X * Y, f);

    fclose(f);


    f = fopen("gradient_text.ppm", "wb");

    fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            fprintf(f, "%d %d %d\n", raster[y][x][R],
                raster[y][x][G], raster[y][x][B]);
        }
    }
    fclose(f);

  
    return 0;
}