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
        for(i = 0; i < image_width; i++){
            r = (double) i / (image_width-1);
            g = (double) j / (image_height-1);
            b = 0.0;

            int ir = (int)255.999 * r;
            int ig = (int)255.999 * g;
            int ib = (int)255.999 * b;

            fprintf(f, "%d %d %d\n",
                (unsigned char) (ir),
                (unsigned char) (ig),
                (unsigned char) (ib));
        }
    }
    fclose(f);
    return 0;
}