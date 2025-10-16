#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(FILE *f, const color& pixel_color){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

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