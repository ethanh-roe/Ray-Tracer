#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"

#include <stdio.h>

int main(int argc, char *argv[]){

    int i,j;
    double r,g,b;
    FILE *f;

    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    f = fopen("test_image.ppm", "w");
    fprintf(f, "P3\n%d\n%d\n255\n", image_width, image_height);
    for(j = 0; j < image_height; j++){
        fprintf(stderr, "\rScanlines remaining: %d ", image_height - j);
        fflush(stderr);  // make sure it prints immediately
        for(i = 0; i < image_width; i++){

            color pixel_color = {
                (double) i / (image_width-1),
                (double) j / (image_height-1),
                0.0
            };

            write_color(f, pixel_color);
        }
    }
    fprintf(stderr, "\rDone.                 \n");
    fclose(f);
    return 0;
}