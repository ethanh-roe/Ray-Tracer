#ifndef VEC3_H
#define VEC3_H

 // Index 0 is x dim, 1 is y dim, 2 is z dim
 typedef double vec3[3];

 struct triangle {
    vec3 v1, v2, v3;
    vec3 n; // normal
 };

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
 #endif