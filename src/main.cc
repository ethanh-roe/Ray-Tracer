#include "../include/common_consts.h"

#include "../include/bvh.h"
#include "../include/camera.h"
#include "../include/constant_medium.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/material.h"
#include "../include/mesh_loader.h"
#include "../include/quad.h"
#include "../include/sphere.h"
#include "../include/texture.h"
#include "../include/triangle.h"


#include <iostream>
#include <string>
#include <sstream>

void bouncing_spheres(){
    hittable_list world;

    // auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    // world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    auto checker = make_shared<checker_texture>(0.32, color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    world = hittable_list(make_shared<bvh_node>(world));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;
    
    cam.render(world, lights);
}

void checkered_spheres() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

    world.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void test_scene1(){
    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));

    // Moving sphere
    point3 center(0.9*random_double(), 0.2, 0.9*random_double());
    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
    world.add(make_shared<sphere>(center, center2, 0.2, material_right));
    
    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 400;
    cam.samples_per_pixel   = 1000;
    cam.max_depth           = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.lookfrom = point3(0, 1, 5);
    cam.lookat   = point3(0, 0, -1);
    cam.vup      = vec3(0, 1, 0);
    
    cam.defocus_angle = 0.0;
    cam.focus_dist = 1.5;

    cam.render(world, lights);
}

void earth() {
    hittable_list world;
    
    auto earth_texture = make_shared<image_texture>("../media/earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);

    world.add(globe);

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.lookfrom = point3(0,0,12);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void perlin_spheres() {
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void quads() {
    hittable_list world;

    // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 80;
    cam.lookfrom = point3(0,0,9);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void simple_light() {
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
    auto sphere_light = make_shared<sphere>(point3(0, 7, 0), 2, difflight);
    auto quad_light = make_shared<quad>(point3(3, 1, -2), vec3(2, 0, 0), vec3(0, 2, 0), difflight);

    world.add(sphere_light);
    world.add(quad_light);

    // Light Sources
    hittable_list lights;
    lights.add(sphere_light);
    lights.add(quad_light);

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 20;
    cam.lookfrom = point3(26,3,6);
    cam.lookat   = point3(0,2,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void cornell_box() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // Room
    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(555,555,555), vec3(-555,0,0), vec3(0,0,-555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));

    // Light
    world.add(make_shared<quad>(point3(213,554,227), vec3(130,0,0), vec3(0,0,105), light));

    // Box
    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    // Glass Sphere
    auto glass = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(190,90,190), 90, glass));

    // Light Sources
    auto empty_material = shared_ptr<material>();
    hittable_list lights;
    lights.add(make_shared<quad>(point3(343,554,332), vec3(-130,0,0), vec3(0,0,-105), empty_material));
    lights.add(make_shared<sphere>(point3(190, 90, 190), 90, empty_material));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void cornell_smoke() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<quad>(point3(113,554,127), vec3(330,0,0), vec3(0,0,305), light));
    world.add(make_shared<quad>(point3(0,555,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));

    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = box(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));

    world.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    world.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));

    // Light Sources
    auto empty_material = shared_ptr<material>();
    hittable_list lights;
    lights.add(make_shared<quad>(point3(113,554,127), vec3(330,0,0), vec3(0,0,305), empty_material));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void final_scene(int image_width, int samples_per_pixel, int max_depth) {
    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(box(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hittable_list world;

    world.add(make_shared<bvh_node>(boxes1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    world.add(make_shared<quad>(point3(123,554,147), vec3(300,0,0), vec3(0,0,265), light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    world.add(make_shared<sphere>(center1, center2, 50, sphere_material));

    world.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(
        point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0,0,0), 5000, make_shared<dielectric>(1.5));
    world.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("../media/earthmap.jpg"));
    world.add(make_shared<sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.2);
    world.add(make_shared<sphere>(point3(220,280,300), 80, make_shared<lambertian>(pertext)));

    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<sphere>(point3::random(0,165), 10, white));
    }

    world.add(make_shared<translate>(
        make_shared<rotate_y>(
            make_shared<bvh_node>(boxes2), 15),
            vec3(-100,270,395)
        )
    );

    // Light Sources
    auto empty_material = shared_ptr<material>();
    hittable_list lights;
    lights.add(make_shared<quad>(point3(123,554,147), vec3(300,0,0), vec3(0,0,265), empty_material));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = image_width;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth         = max_depth;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(478, 278, -600);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void triangle_scene() {
    hittable_list world;

    // Materials
    auto red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto blue    = make_shared<lambertian>(color(0.2, 0.2, 1.0));

    // Triangles
    world.add(make_shared<triangle>(point3(-3, -2, 5), point3(-3, -2, 1), point3(-3, 2, 5), red));
    world.add(make_shared<triangle>(point3(-2, -2, 0), point3( 2, -2, 0), point3(-2, 2, 0), green));
    world.add(make_shared<triangle>(point3( 3, -2, 1), point3( 3, -2, 5), point3( 3, 2, 1), blue));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 80;
    cam.lookfrom = point3(0,0,9);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void pyramid_scene() {
    hittable_list world;

    // Materials
    auto red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto blue    = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto orange  = make_shared<lambertian>(color(1.0, 0.6, 0.2));
    auto yellow  = make_shared<lambertian>(color(1.0, 1.0, 0.2));

    auto pertext = make_shared<noise_texture>(4);
    
    // Square base points
    point3 A(-1, 0, -1);
    point3 B(1, 0, -1);
    point3 C(1, 0, 1);
    point3 D(-1, 0, 1);

    // Pyramid apex
    point3 apex(0, 2, 0);

    // Base triangles
    world.add(make_shared<triangle>(A, B, C, yellow));
    world.add(make_shared<triangle>(A, C, D, yellow));

    // Triangles
    world.add(make_shared<triangle>(apex, A, B, red));
    world.add(make_shared<triangle>(apex, B, C, green));
    world.add(make_shared<triangle>(apex, C, D, blue));
    world.add(make_shared<triangle>(apex, D, A, orange));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 50;
    cam.lookfrom = point3(4,-2,4);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void perlin_pyramid_scene(){
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    
    // Square base points
    point3 A(-1, 0, -1);
    point3 B(1, 0, -1);
    point3 C(1, 0, 1);
    point3 D(-1, 0, 1);

    // Pyramid apex
    point3 apex(0, 2, 0);

    // Base triangles
    world.add(make_shared<triangle>(A, B, C, make_shared<lambertian>(pertext)));
    world.add(make_shared<triangle>(A, C, D, make_shared<lambertian>(pertext)));

    // Triangles
    world.add(make_shared<triangle>(apex, A, B, make_shared<lambertian>(pertext)));
    world.add(make_shared<triangle>(apex, B, C, make_shared<lambertian>(pertext)));
    world.add(make_shared<triangle>(apex, C, D, make_shared<lambertian>(pertext)));
    world.add(make_shared<triangle>(apex, D, A, make_shared<lambertian>(pertext)));

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);

    cam.vfov     = 50;
    cam.lookfrom = point3(4,-2,4);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}

void stanford_bunny_mesh_scene(){
    hittable_list world;

    auto red_mat = make_shared<lambertian>(color(1.0,0.2,0.2));

    // Load a mesh
    auto bunny_mesh = mesh_loader::load_obj("obj/stanford-bunny.obj", red_mat);
    
    aabb mesh_bounds = bunny_mesh->bounding_box();
    point3 mesh_center = mesh_bounds.center();
    vec3 mesh_size = mesh_bounds.max() - mesh_bounds.min();
    double radius = mesh_size.length() * 0.5;

    auto mesh_bvh = make_shared<bvh_node>(bunny_mesh->objects, 0, bunny_mesh->objects.size());

    world.add(mesh_bvh);

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;
    cam.lookfrom = mesh_center + vec3(0, radius, radius * 3);
    cam.lookat   = mesh_center;
    cam.vup      = vec3(0,1,0);
    cam.vfov     = 40;
    cam.aspect_ratio = 1.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 1000;
    cam.background = color(0.7, 0.8, 1.0);

    cam.render(world, lights);
}

void armadillo_mesh_scene() {
    hittable_list world;

    auto red_mat = make_shared<lambertian>(color(1.0,0.2,0.2));

    // Load a mesh
    auto armadillo_mesh = mesh_loader::load_obj("obj/armadillo.obj", red_mat);

    aabb mesh_bounds = armadillo_mesh->bounding_box();
    point3 mesh_center = mesh_bounds.center();
    vec3 mesh_size = mesh_bounds.max() - mesh_bounds.min();
    double radius = mesh_size.length() * 0.5;

    auto mesh_bvh = make_shared<bvh_node>(armadillo_mesh->objects, 0, armadillo_mesh->objects.size());

    world.add(mesh_bvh);

    // Light Sources
    hittable_list lights;
    auto dummy_light = make_shared<diffuse_light>(color(0, 0, 0));
    lights.add(make_shared<quad>(point3(0, 0, -1000), vec3(1000, 0, 0), vec3(0, 1000, 0), dummy_light));

    camera cam;

    cam.lookfrom = mesh_center - vec3(0, radius / -2, radius * 2);
    cam.lookat   = mesh_center;
    cam.vup      = vec3(0,1,0);
    cam.vfov     = 40;
    cam.aspect_ratio = 1.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 1000;
    cam.background = color(0.7, 0.8, 1.0);

    cam.render(world, lights);
}

int main(int argc, char *argv[]){
    int selected_scene = 0; // Default scene is 8 (cornell box).
    string input;

    cout << "(0)  Bouncing Spheres <-- Default" << endl;
    cout << "(1)  Checkered Spheres"            << endl;
    cout << "(2)  Test"                         << endl;
    cout << "(3)  Earth"                        << endl;
    cout << "(4)  Perlin Noise Spheres"         << endl;
    cout << "(5)  Quads"                        << endl;
    cout << "(6)  Simple Light"                 << endl;
    cout << "(7)  Cornell Box"                  << endl;
    cout << "(8)  Cornell Box with Smoke Scene" << endl;
    cout << "(9)  Final Scene"                  << endl;
    cout << "(10) Triangle Scene"               << endl;
    cout << "(11) Pyramid Scene"                << endl;
    cout << "(12) Perlin Pyramid Scene"         << endl;
    cout << "(13) Stanford Bunny Mesh Scene"    << endl;
    cout << "(14) Armadillo Mesh Scene"         << endl;

    cout << "Select a scene: ";
    
    getline(cin, input);

    if(!input.empty()) {
        stringstream stream(input);
        if(!(stream >> selected_scene) || selected_scene < 0 || selected_scene > 14){
            cout << "Invalid input. Using default scene" << endl;
            selected_scene = 7;
        }
    }
    
    switch (selected_scene) {
        case 0: 
        cout << "Rendering Bouncing Spheres Scene" << endl;
        bouncing_spheres();
        break;

        case 1: 
        cout << "Rendering Checkered Spheres Scene" << endl;
        checkered_spheres();
        break;

        case 2: 
        cout << "Rendering Test Scene" << endl;
        test_scene1();
        break;

        case 3: 
        cout << "Rendering Earth Scene" << endl;
        earth();
        break;

        case 4: 
        cout << "Rendering Perlin Noise Spheres Scene" << endl;
        perlin_spheres();
        break;

        case 5: 
        cout << "Rendering Quads Scene" << endl;
        quads();
        break;

        case 6: 
        cout << "Rendering Simple Light Scene" << endl;
        simple_light();
        break;

        case 7: 
        cout << "Rendering Cornell Box Scene" << endl;
        cornell_box();
        break;

        case 8:
        cout << "Rendering Cornell Box with Smoke Scene" << endl;
        cornell_smoke();
        break;

        case 9:
        cout << "Rendering Final Sceen" << endl;
        final_scene(800, 10000, 50);
        break;

        case 10:
        cout << "Rendering Triangle Scene" << endl;
        triangle_scene();
        break;

        case 11:
        cout << "Rendering Pyramid Scene" << endl;
        pyramid_scene();
        break;

        case 12:
        cout << "Rendering Perlin Pyramid Scene" << endl;
        perlin_pyramid_scene();
        break;

        case 13:
        cout << "Rendering Stanford Bunny Mesh" << endl;
        stanford_bunny_mesh_scene();
        break;

        case 14:
        cout << "Rendering Armadillo Mesh" << endl;
        armadillo_mesh_scene();
        break;
    }
    return 0;
}