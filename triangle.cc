#include "triangle.h"
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

triangle::triangle (const myPoint &P1, const myPoint &P2, const myPoint &P3) {
	p1 = P1;
	p2 = P2;
	p3 = P3;
	pos.x = (p1[0]+p2[0]+p3[0]) / 3;
	pos.y = (p1[1]+p2[1]+p3[1]) / 3;
	pos.z = (p1[2]+p2[2]+p3[2]) / 3;
	myVector ab = p2-p1;
	myVector ac = p3-p1;
	normal = ab.cross(ac);
	normal = normal.getUnitVec();
	
	float bbminx, bbminy, bbminz, bbmaxx, bbmaxy, bbmaxz;
	bbminx = min(min(p1.x, p2.x), p3.x);
	bbminy = min(min(p1.y, p2.y), p3.y);
	bbminz = min(min(p1.z, p2.z), p3.z);
	bbmaxx = max(max(p1.x, p2.x), p3.x);
	bbmaxy = max(max(p1.y, p2.y), p3.y);
	bbmaxz = max(max(p1.z, p2.z), p3.z);
	
	if (bbmaxx == bbminx) {
		bbmaxx += 0.001;
	}
	if (bbmaxy == bbminy) {
		bbmaxy += 0.001;
	}
	if (bbmaxz == bbminz) {
		bbmaxz += 0.001;
	}
	
	myPoint min(bbminx, bbminy, bbminz);
	myPoint max(bbmaxx, bbmaxy, bbmaxz);
	box = bbox(min, max);
}

bool triangle::intersect(ray* rayPtr, int sf_id, bool useBbox, intersection *&ipoint){
	
	myPoint rayPos = rayPtr->getPos();
	myVector rayDir = rayPtr->getDir();
	
	float intersectionT;

	if (!box.intersect(rayPtr, intersectionT)){
		// cout << intersectionT << endl;
		return false;
	}

	if (useBbox) {
		myPoint itrPt = rayPos+(rayDir * intersectionT);
		
		myVector n = box.getNormal(itrPt);
		intersection *data = new intersection(sf_id, intersectionT, n, rayDir, itrPt, mtr);
		ipoint = data;
		rayPtr->addIntersection(data);
		return true;
	}
	 
	float a = p1[0] - p2[0];
	float b = p1[1] - p2[1];
	float c = p1[2] - p2[2];
	float d = p1[0] - p3[0];
	float e = p1[1] - p3[1];
	float f = p1[2] - p3[2];
	float g = rayDir[0];
	float h = rayDir[1];
	float i = rayDir[2];
	float j = p1[0] - rayPos[0];
	float k = p1[1] - rayPos[1];
	float l = p1[2] - rayPos[2];
	float A = e*i - h*f;
	float B = g*f - d*i;
	float C = d*h - e*g;
	float D = a*k- j*b;
	float E = j*c- a*l;
	float F = b*l - k*c;
	float M = a*A+b*B+c*C;
	
	float t = -(f*D+e*E +d*F)/M;
	if(t<0) return false;
	  myPoint itrPt = rayPos+(rayDir * t);
	
	float gamma = (i*D+h*E+g*F)/M;
	if(gamma<0 || gamma >1) return false;
	
	float beta = (j*A+k*B+l*C)/M;
	if(beta<0 || beta>(1-gamma)) return false;
	
	myVector v = rayDir * (-1.0f);
	intersection *data = new intersection(sf_id, t, normal, v,  itrPt, mtr);
	ipoint = data;
	rayPtr->addIntersection(data);
	
	return true;
}