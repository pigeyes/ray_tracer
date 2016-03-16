//
//  plane.h
//  
//
//  Created by ChuMingChing on 2/16/16.
//
//

#ifndef plane_h
#define plane_h

#include <stdio.h>
#include "surface.h"
#include "ray.h"

class plane : public surface{
public:
	plane(myVector vec, float D): normal(vec), d(D){}
	bool intersect(ray* , int, bool, intersection*&);
private:
	myVector normal;
	float d;
};

#endif /* plane_h */
