#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * orthographic camera instead of perspective camera
 * 
 * 
 * Perspective Projection:
 * Parallel lines will converge, except those 
 * that are orthogonal to the view direction.
 * 
 * Orthogonal Projection:
 * Lines come from 2D plane and travel in a 
 * parallel direction instead of firing rays out
 * at different angles from a perspective.
 * (Mainly used for engineering drawings, all 
 * parallel lines, regardless of orientation, stay
 * parallel.)
 */

 #define X 1024
 #define Y 1024


 // Zero possible and get as close as possible to 1 without hitting it.
 #define frand() (rand() / (RAND_MAX + 1.0))

 #define SAMPLES_PER_PIXEL 1000

 // Enables aliasing
 #define ALIASING 0

 // Index 0 is x dim, 1 is y dim, 2 is z dim
 typedef double vec3[3];

 struct triangle {
    vec3 v1, v2, v3;
    vec3 n; // normal
 } ;
 
 double vec3_dot(vec3 v, vec3 w)
 {
    return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
 }

 /**
  * i  j  k
  * v0 v1 v2
  * w0 w1 w2
  */
 void vec3_cross(vec3 out, vec3 v, vec3 w)
 {
    out[0] = v[1] * w[2] - v[2] * w[1];  
    out[1] =  v[2] * w[0] - v[0] * w[2]; //-(v[0] * w[2] - v[2] * w[0])
    out[2] = v[0] * w[1] - v[1] * w[0];
 }

 void vec3_sub(vec3 out, vec3 v, vec3 w)
 {
    out[0] = v[0] - w[0];
    out[1] = v[1] - w[1];
    out[2] = v[2] - w[2];
 }

 double image[Y][X][3]; // Zero by placement

 int main(int argc, char *argv[])
{
    int y, x, s;
    double dy, dx, sy, sx;
    FILE *f;
    vec3 p;
    vec3 v1, v2;
    vec3 na, nb, nc, n;
    vec3 bary;

    // Make triangle
    struct triangle t;
    t.v1[0] = -0.5;
    t.v1[1] = -0.5;
    t.v1[2] = -1.0;

    t.v2[0] = 0.0;
    t.v2[1] = 0.0;
    t.v2[2] = -1.0;

    t.v3[0] = -0.25;
    t.v3[1] = 0.5;
    t.v3[2] = -1.0;

    // n = (b - a) x (c - a)
    vec3_sub(v1, t.v2, t.v1);
    vec3_sub(v2, t.v3, t.v1);
    vec3_cross(n, v1, v2);

    // Produce image
    
    for(y = 0; y < Y; y++){
        for(x = 0; x < X; x++){
            // For aliasing, 
            if(ALIASING == 1){
                for(s = 0; s < SAMPLES_PER_PIXEL; s++){
                    /**
                     * This is aliased but has bad sampling
                     * Also only works with 4 samples per pixel
                    switch(s){
                        case 0:
                        sx = -(1.0 / (2.0 * X));
                        sy = -(1.0 / (2.0 * Y));
                        break;
                        case 1:
                        sx = (1.0 / (2.0 * X));
                        sy = -(1.0 / (2.0 * Y));
                        break;
                        case 2:
                        sx = -(1.0 / (2.0 * X));
                        sy = (1.0 / (2.0 * Y));
                        break;
                        case 3:
                        sx = (1.0 / (2.0 * X));
                        sy = (1.0 / (2.0 * Y));
                        break;
    
                    }
                    */
                    // Get a random number. Scale it to the dimensions of the pixel
                    // The subtract half a pixel.
                    sx = (frand() / X) - (1.0 / (2.0 * X));
                    sy = (frand() / Y) - (1.0 / (2.0 * Y));
    
                    dx = ((x - (X / 2.0)) / (X / 2.0)) + (1 / X) + sx;
                    dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1 / Y) + sy;
    
                    p[0] = dx;
                    p[1] = dy;
                    p[2] = -1.0; // Triangle place is at -1
    
                    // na = (c - b) x (p - b)
                    vec3_sub(v1, t.v3, t.v2);
                    vec3_sub(v2, p, t.v2);
                    vec3_cross(na, v1, v2);
    
                    // nb = (a - c) x (p - c)
                    vec3_sub(v1, t.v1, t.v3);
                    vec3_sub(v2, p, t.v3);
                    vec3_cross(nb, v1, v2);
                    // nc = (b - a) x (p - a)
                    vec3_sub(v1, t.v2, t.v1);
                    vec3_sub(v2, p, t.v1);
                    vec3_cross(nc, v1, v2);
    
                    bary[0] = vec3_dot(n, na) / vec3_dot(n, n);
                    bary[1] = vec3_dot(n, nb) / vec3_dot(n, n);
                    bary[2] = vec3_dot(n, nc) / vec3_dot(n, n);
    
                    // check if we hit something
                    // 1 is max brightness, 0 is min brightness
                    if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0){
                        image[y][x][0] = image[y][x][1] = image[y][x][2] += 1.0;    
    
                        // For gradual colors
                        // image[y][x][0] = bary[0];
                        // image[y][x][1] = bary[1];
                        // image[y][x][2] = bary[2];
                    }
                }
            } else{
                dx = ((x - (X / 2.0)) / (X / 2.0)) + (1 / X);
                dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1 / Y);
    
                p[0] = dx;
                p[1] = dy;
                p[2] = -1.0; // Triangle place is at -1
    
                // na = (c - b) x (p - b)
                vec3_sub(v1, t.v3, t.v2);
                vec3_sub(v2, p, t.v2);
                vec3_cross(na, v1, v2);

                // nb = (a - c) x (p - c)
                vec3_sub(v1, t.v1, t.v3);
                vec3_sub(v2, p, t.v3);
                vec3_cross(nb, v1, v2);
                // nc = (b - a) x (p - a)
                vec3_sub(v1, t.v2, t.v1);
                vec3_sub(v2, p, t.v1);
                vec3_cross(nc, v1, v2);

                bary[0] = vec3_dot(n, na) / vec3_dot(n, n);
                bary[1] = vec3_dot(n, nb) / vec3_dot(n, n);
                bary[2] = vec3_dot(n, nc) / vec3_dot(n, n);

                // check if we hit something
                // 1 is max brightness, 0 is min brightness
                if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0){
                    // image[y][x][0] = image[y][x][1] = image[y][x][2] += 1.0;

                    // For gradual colors
                    image[y][x][0] = bary[0];
                    image[y][x][1] = bary[1];
                    image[y][x][2] = bary[2];
                }
            }
            
        }
    }
    // Write image
    f = fopen("barycentric.ppm", "w");
    fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
    
    // iterate over our space
    for(y = Y - 1; y >= 0; y--){
        for(x = 0; x < X; x++){
            if (ALIASING == 1){
                fprintf(f, "%d %d %d\n",
                    (unsigned char) (image[y][x][0] * 255.99 / SAMPLES_PER_PIXEL),
                    (unsigned char) (image[y][x][1] * 255.99 / SAMPLES_PER_PIXEL),
                    (unsigned char) (image[y][x][2] * 255.99 / SAMPLES_PER_PIXEL));
            } else{
                fprintf(f, "%d %d %d\n",
                    (unsigned char) (image[y][x][0] * 255.99),
                    (unsigned char) (image[y][x][1] * 255.99),
                    (unsigned char) (image[y][x][2] * 255.99));
            }
            
        }
    }
    return 0;
}