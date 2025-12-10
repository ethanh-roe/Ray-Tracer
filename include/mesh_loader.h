#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "triangle.h"
#include "hittable_list.h"
#include "material.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

namespace mesh_loader {
    
    inline shared_ptr<hittable_list> load_obj(const string& filename, shared_ptr<material> mat) {
        ifstream in(filename);
        if(!in) throw runtime_error("Could not open the obj file: " + filename);

        vector<point3> vertices;
        auto mesh = make_shared<hittable_list>();

        string line;
        while(getline(in, line)){
            istringstream iss(line);
            string type;
            iss >> type;

            if(type == "v") {
                double x, y, z;
                iss >> x >> y >> z;
                vertices.push_back(point3(x, y, z));
            } else if(type == "f") {
                int i, j, k;
                iss >> i >> j >> k;

                mesh->add(make_shared<triangle>(vertices[i - 1], vertices[j - 1], vertices[k - 1], mat));
            }
        }
        return mesh;
    }
};

#endif