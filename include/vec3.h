#ifndef VEC3_H
#define VEC3_H
class vec3{
   public:
      double e[3];
      vec3() : e{0,0,0} {}
      vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
   
      double x() const { return e[0]; }
      double y() const { return e[1]; }
      double z() const { return e[2]; }

      double operator[](int i) const {return e[i]; }
      double& operator[](int i) {return e[i]; }
};

// for clarity, refer to this class as point3
using point3 = vec3;

// Utility Functions

inline double dot(vec3 v, vec3 w){
   return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
}

inline vec3 cross(vec3 v, vec3 w){
   return vec3(
   v[1] * w[2] - v[2] * w[1],  
   v[2] * w[0] - v[0] * w[2], 
   v[0] * w[1] - v[1] * w[0]
   );
}

inline vec3 sub(vec3 v, vec3 w){
   return vec3(
      v[0] - w[0],
      v[1] - w[1],
      v[2] - w[2]
   );
}
 #endif