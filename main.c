#include <stdio.h>

int main(int argc, char *argv[]){

    int i,j;
    double r,g,b;
    FILE *f;

    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    fopen("test_image.ppm", "w");
    fprintf(f, "P3\n%d\n%d\n255\n", image_width, image_height);
    for(i = 0; i < image_height; i++){
        for(j = 0; j < image_width; j++){
            r = i / (image_width-1);
            g = j / (image_height-1);
            b = 0.0;

            // int ir = 255.999 * r;
            // int ig = 255.999 * g;
            // int ib = 255.999 * b;

            fprintf(f, "%d %d %d\n",
                (unsigned char) (r * 255.99),
                (unsigned char) (g * 255.99),
                (unsigned char) (b * 255.99));
        }
    }

    return 0;
}