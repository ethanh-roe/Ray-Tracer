/**
 *  Texturing allows us to use images to apply colors to objects
 * 
 *  - Probably want to store textures floating point colors in [0,1),
 *  because youll only need to scale the data once.
 * 
 *  - To texture an object, we need a mapping, <u, v> -> range [0,1), from the surface
 *  of the object into the texture space. 
 * 
 *  - If loaded data is in [0,255] get it in the range [0,1) by dividing by 256.
 * 
 *  - A pixel in a texture is called a texel.
 *  - Getting texture coordinates on the surface of a sphere, 
 *  convert from <x,y,z> to <theta, phi> and then to <u,v>
 *      y = cos(theta)
 *      z = sin(theta)sin(phi)
 *      x = sin(theta) cos(phi)
 *  Our ray has already hit the sphere at <x,y,z>. So we are aware of the 
 *  coordinates and we want to color it. So we need to solve for theta and psi.
 *  
 *  Adjust to make signs more convenient
 *  y = -cos(theta)
 *  x = sin(theta)cos(phi)
 *  z = sin(theta)sin(phi)
 * 
 *  theta = arccos(-y) -> in range [0,pi)
 *  phi = arctan2(-z,x) + pi -> in range [0, 2pi]
 *  u =(phi / 2pi)
 *  v = (theta / pi)
 */