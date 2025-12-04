#include "../include/common_consts.h"

#include "../include/camera.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"

#include <stdio.h>

#define ALIASING 0

#define SAMPLES_PER_PIXEL 4

int main(int argc, char *argv[]){

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    
    cam.render(world);
    return 0;
}