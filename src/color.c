#include "../include/color.h"

void write_color(FILE *f, color pixel_color)
{
    double r = pixel_color.r;
    double g = pixel_color.g;
    double b = pixel_color.b;

    // translate the [0,1] component values ot the byte range [0,255]
    int ir = (int)255.999 * r;
    int ig = (int)255.999 * g;
    int ib = (int)255.999 * b;

    fprintf(f, "%d %d %d\n",
                (unsigned char) (ir),
                (unsigned char) (ig),
                (unsigned char) (ib));
}