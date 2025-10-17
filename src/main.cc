#include "../include/vec3.h"
#include "../include/color.h"
// #include "../include/ray.h"

#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 1024

#define ALIASING 0

#define SAMPLES_PER_PIXEL 4

int main(int argc, char *argv[]){

    int i,j,s;
    double r,g,b;
    FILE *f;

    // Render
    f = fopen("test_image.ppm", "w");
    fprintf(f, "P3\n%d\n%d\n255\n", WIDTH, HEIGHT);
    for(j = 0; j < HEIGHT; j++){
        fprintf(stderr, "\rScanlines remaining: %d ", HEIGHT - j);
        fflush(stderr);  // make sure it prints immediately
        for(i = 0; i < WIDTH; i++){

            if(ALIASING == 1){
                for(s = 0; s < SAMPLES_PER_PIXEL; s++){

                }
            }

            color pixel_color = {
                (double) i / (WIDTH-1),
                (double) j / (HEIGHT-1),
                0.0
            };

            write_color(f, pixel_color);
        }
    }
    fprintf(stderr, "\rDone.                 \n");
    fclose(f);
    return 0;
}