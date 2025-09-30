#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef struct color{
    double r;
    double g;
    double b;
} color;

void write_color(FILE *f, color pixel_color);

#endif