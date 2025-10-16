#include "../include/vec3.h"

 double vec3_dot(vec3 v, vec3 w)
 {
    return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
 };

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
 };

  void vec3_sub(vec3 out, vec3 v, vec3 w)
 {
    out[0] = v[0] - w[0];
    out[1] = v[1] - w[1];
    out[2] = v[2] - w[2];
 };