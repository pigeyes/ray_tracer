//
//  plane.cc
//  
//
//  Created by ChuMingChing on 2/16/16.
//
//

#include "plane.h"

bool plane::intersect(ray* rayPtr, int sf_id, bool useBbox, intersection *&ipoint){
	myPoint rayPos = rayPtr->getPos();
	myPoint origin(0.0f, 0.0f, 0.0f);
	myVector P0 = rayPos - origin;
	myVector rayDir = rayPtr->getDir();
	
	float denominator = rayDir.dot(normal);
	if(denominator==0) return false;
	else{
		float t = (P0.dot(normal) + d)/denominator;
		t*=-1.0f;
		if(t<0) return false;
		myPoint itrPt = rayPos + (rayDir*t);
		myVector n(normal);
		myVector v = rayDir * (-1.0f);
		intersection* data = new intersection(sf_id, t, n, v,  itrPt, mtr);
		ipoint = data;
		rayPtr->addIntersection(data);
		return true;
	}
}