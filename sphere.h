//
//  sphere.h
//  
//
//  Created by ChuMingChing on 2/10/16.
//
//

#ifndef sphere_h
#define sphere_h

#include "surface.h"
#include "ray.h"

class sphere : public surface{
public:
	sphere(float x, float y, float z, float r); // constructor
	bool intersect(ray*, int, bool useBbox, intersection *&ipoint); // override surface::intersect
	
	float radius;
};

#endif /* sphere_h */
