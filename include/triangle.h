#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable {
    public:
        triangle(const point3& a, const vec3& b, const vec3& c, shared_ptr<material> mat)
            : v0(a), v1(b), v2(c), mat(mat) {
                normal = unit_vector(cross(v1 - v0, v2 - v0));
                D = dot(normal, v0);
                set_bounding_box();
            }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            auto denom = dot(normal, r.direction());
            if(fabs(denom) < 1e-8) return false;

            auto t = (D - dot(normal, r.origin())) / denom;
            if(!ray_t.contains(t)) return false;

            point3 P = r.at(t);

            // Barycentric
            vec3 u = v1 - v0;
            vec3 v = v2 - v0;
            vec3 w = P - v0;

            double uu = dot(u, u);
            double uv = dot(u, v);
            double vv = dot(v, v);
            double wu = dot(w, u);
            double wv = dot(w, v);
            double denom_bary = uv * uv - uu * vv;

            double s = (uv * wv - vv * wu) / denom_bary;
            double t_bary = (uv * wu - uu * wv) / denom_bary;

            if(s < 0 || t_bary < 0 || (s + t_bary) > 1) return false;

            rec.t = t;
            rec.p = P;
            rec.mat = mat;
            rec.set_face_normal(r, normal);
            rec.u = s;
            rec.v = t_bary;
            return true;
        }

        aabb bounding_box() const override { return bbox; }

    private:
        point3 v0, v1, v2;
        vec3 normal;
        double D;
        shared_ptr<material> mat;
        aabb bbox;

        void set_bounding_box() {
            point3 min(fmin(v0.x(), fmin(v1.x(), v2.x())),
                       fmin(v0.y(), fmin(v1.y(), v2.y())),
                       fmin(v0.z(), fmin(v1.z(), v2.z())));

            point3 max(fmax(v0.x(), fmax(v1.x(), v2.x())),
                       fmax(v0.y(), fmax(v1.y(), v2.y())),
                       fmax(v0.z(), fmax(v1.z(), v2.z())));

            bbox = aabb(min, max);
        }
};

#endif