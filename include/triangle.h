#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "ray.h"

class triangle : public hittable {
    public:
        triangle(const point3& A, const point3& B, const point3& C, shared_ptr<material> mat) 
            : A(A), B(B), C(C), mat(mat) {

                auto n = cross(B - A, C - A);
                normal = unit_vector(n);
                D = dot(normal, A);

                set_bounding_box();
            }

        virtual void set_bounding_box() {
            vec3 min_point(
                    fmin(A.x(), fmin(B.x(), C.x())),
                    fmin(A.y(), fmin(B.y(), C.y())),
                    fmin(A.z(), fmin(B.z(), C.z()))
                );

            vec3 max_point(
                    fmax(A.x(), fmax(B.x(), C.x())),
                    fmax(A.y(), fmax(B.y(), C.y())),
                    fmax(A.z(), fmax(B.z(), C.z()))
                );

            bbox = aabb(min_point, max_point);
        }

        aabb bounding_box() const override { return bbox; }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            // Ray place intersection
            auto denom = dot(normal, r.direction());

            // No hit if ray is parallel to the plane;
            if(fabs(denom) < 1e-8) return false;

            // Return false if the hit point parameter t is outside ray interval
            auto t = (D - dot(normal, r.origin())) / denom;
            if(!ray_t.contains(t)) return false;

            auto P = r.at(t);

            // Barycentric coords
            vec3 v0 = B - A;
            vec3 v1 = C - A;
            vec3 v2 = P - A;

            double d00 = dot(v0, v0);
            double d01 = dot(v0, v1);
            double d11 = dot(v1, v1);
            double d20 = dot(v2, v0);
            double d21 = dot(v2, v1);

            double denom_bary = (d00 * d11) - (d01 * d01);
            double v = (d11 * d20 - d01 * d21) / denom_bary;
            double w = (d00 * d21 - d01 * d20) / denom_bary;
            double u = 1.0 - v - w;

            // Return false if outside of triangle
            if(!is_interior(u, v, rec)) return false;

            rec.t = t;
            rec.p = P;
            rec.mat = mat;
            rec.set_face_normal(r, normal);
            rec.u = u;
            rec.v = v;
            
            return true;
        }

        virtual bool is_interior(double a, double b, hit_record& rec) const {
            interval unit_interval = interval(0, 1);

            if (!unit_interval.contains(a) || !unit_interval.contains(b)) return false;

            rec.u = a;
            rec.v = b;
            return true;
        }

    private:
        point3 A, B, C; // Triangle vertices
        vec3 normal;
        shared_ptr<material> mat;
        aabb bbox;
        double D;
};

#endif