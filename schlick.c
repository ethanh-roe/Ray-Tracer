#include <stdio.h>
#include <math.h>

// rir = radius indices reflection
// cai = cosine angle of incidence
double refraction(double cai, double rir)
{
    double t;
    t = (1-rir)/(1+rir);
    t *= t;
    return t + (1-t) * pow(1-cai, 5.0);
}

//if tir or uniform random in [0,1] < schlick then we reflect else we refract

/**
 * [refracting]
 * r_perp = n/n_1 (r+n cos(theta))
 * r_parr = sqrt(1-|r_perp|^2)
 * 
 * x dot y = |x||y|cos(theta)
 * 
 * if x and y are are under kength
 * 
 * r_perp = n/n_1 (r-(r dot n) cos(theta))
 * -------------------
 * 
 */