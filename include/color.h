#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

void write_color(FILE *f, const color& pixel_color){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // translate the [0,1] component values ot the byte range [0,255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    fprintf(f, "%d %d %d\n",
                (unsigned char) (rbyte),
                (unsigned char) (gbyte),
                (unsigned char) (bbyte));
}

#endif