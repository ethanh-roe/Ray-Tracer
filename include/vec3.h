#ifndef VEC3_H
#define VEC3_H
#include <ostream>
#include <cmath>
class vec3{
   public:
      double e[3];
      vec3() : e{0,0,0} {}
      vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
   
      double x() const { return e[0]; }
      double y() const { return e[1]; }
      double z() const { return e[2]; }

      vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
      double operator[](int i) const {return e[i]; }
      double& operator[](int i) {return e[i]; }

          vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

      double length() const {
         return std::sqrt(length_squared());
      }

      double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

// for clarity, refer to this class as point3
using point3 = vec3;

// Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

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

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
 #endif