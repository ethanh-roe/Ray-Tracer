# Ray-Tracer
A ray tracer I am actively developing for my Intro to Computer Graphics course. The ray tracer was developed mainly using "Ray Tracing in One Weekend - The Book Series" (https://raytracing.github.io/).
The program is interactive, enter the number associated with the scene to render that scene. After a scene is rendered the program must be ran again to render another scene. The renderer will output a .ppm file named image.

# Description of files in include/
## aabb.h
Defines the axis-aligned bounding box (aabb) class used for spatial acceleration.
## bvh.h
Defines the bounding volume hierarhcy (bvh) node class for accelerating ray-intersection tests.
## camera.h
Defines the camera and rendering loop for generating rays, applying effects like depth of field and motion blur, and sampling the image.
## color.h
Defines utility function for writing RGB colors as well as gamma correction.
## common_consts.h
Defines common mathmatical functions and constants used through the program as well as common headers.
## constant_medium.h
Defines the constant_medium class which represents volumes like fog and smoke.
## hittable_list.h
Defines a container for storing multiple hittables. 
## hittable.h
Defines an abstract class for renderable objects. Also defines classes for rotating and translating objects.
## interval.h
Defines an interval class used for simplifying intersection testing.
## material.h
Defines an abstract material class along with lambertian, metal, dielectric, diffuse, and isotropic materials. 
## mesh_loader.h
Handles loading of triangle meshes from .obj files into triangle objects using the stb_image library. 
## onb.h
Defines an orthonormal basis class for converting sample coordinates into world space coordinates during sampling.
## pdf.h
Defines probability density functions used for importance sampling. These include sphere, cosine, hittable and mixture pdf classes.
## perlin.h
Defines a perlin noise class for generating perlin noise textures.
## quad.h
Defines a quad class for representing quadrilateral shapes, defined by a point, two vectors, and a material. Includes intersection and area testing functions and a function for creating a bounding box.
## ray.h
Defines the ray class for storing the origin, direction and a time parameter for a particular ray. The time parameter is used for a motion blur effect.
## rtw_stb_image.h
Helper class used for loading image texture into the renderer.
## sphere.h
Defines a quad class for representing spherical shapes, defined by a center point, radius and material. Includes intersection and area testing functions and a function for creating a bounding box.
Defines classes for texture types such as solid textures, checkered textures, image textures, and perlin noise textures. 
## triangle.h
Defines a triangle class for representing triangular shapes, defined by three points and a material. Includes intersection and area testing functions and a function for creating a bounding box.
## vec3.h
Defines a three dimensional vector class for storing points, directions and normals. Also includes vector math functions such as cross and dot products.