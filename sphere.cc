#include <cmath>
#include "sphere.h"

sphere::sphere (float x, float y, float z, float r) {
	radius = r;
	pos = myPoint(x, y, z);
	myPoint min, max;
	min.x = x - r;
	max.x = x + r;
	min.y = y - r;
	max.y = y + r;
	min.z = z - r;
	max.z = z + r;
	
	box.min = min;
	box.max = max;
}

bool sphere::intersect(ray* rayPtr, int sf_id, bool useBbox, intersection *&ipoint){
	myPoint rayPos = rayPtr->getPos();
	myVector rayDir = rayPtr->getDir();

	float intersectionT;
	if (!box.intersect(rayPtr, intersectionT))
		return false;
	if (useBbox) {
		float t = intersectionT;
		myPoint itrPt = rayPos+(rayDir * t);

		myVector n = box.getNormal(itrPt);
		intersection *data = new intersection(sf_id, t, n, rayDir, itrPt, mtr);
		ipoint = data;
		rayPtr->addIntersection(data);
		return true;
	}

	myVector vec1 = rayPos - this->pos;
	float A = rayDir.dot(vec1);
	float B = rayDir.dot(rayDir);
	float C = vec1.dot(vec1)-radius*radius;
	if(A*A-B*C>=0){
		float t1 = (-A - sqrt(A*A-B*C))/B;
		float t2 = (-A + sqrt(A*A-B*C))/B;
		if(t1<0 || t2<0) return false;
		float t = (t1<t2)? t1:t2;
		myPoint itrPt = rayPos+(rayDir * t); //intersect point = P0+td
		
		myVector vec3 = itrPt - this->pos;
		myVector n(vec3.getUnitVec());
		myVector v = rayDir * (-1.0f);
		intersection* data = new intersection(sf_id, t, n, v, itrPt, mtr);
		ipoint = data;
		rayPtr->addIntersection(data);
		return true;
	}
	else return false;
	
}