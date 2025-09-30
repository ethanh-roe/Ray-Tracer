#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

void write_color(FILE *f, color pixel_color)
{
    double r = pixel_color[0];
    double g = pixel_color[1];
    double b = pixel_color[2];

    // translate the [0,1] component values ot the byte range [0,255]
    int ir = (int)255.999 * r;
    int ig = (int)255.999 * g;
    int ib = (int)255.999 * b;

    fprintf(f, "%d %d %d\n",
                (unsigned char) (ir),
                (unsigned char) (ig),
                (unsigned char) (ib));
}
#endif