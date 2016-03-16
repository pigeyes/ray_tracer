//
//  myPoint.cc
//  
//
//  Created by ChuMingChing on 2/8/16.
//
//

#include "myPoint.h"

using namespace std;

myPoint& myPoint::operator+=(const myVector &vec){
	x = x+vec.dx;
	y = y+vec.dy;
	z = z+vec.dz;
	return (*this);
}
myPoint& myPoint::operator-=(const myVector &vec){
	x = x-vec.dx;
	y = y-vec.dy;
	z = z-vec.dz;
	return (*this);
}

const myPoint myPoint::operator+(const myVector &vec){
	return myPoint(*this)+=vec;
}

const myPoint myPoint::operator-(const myVector &vec){
	return myPoint(*this)-=vec;
}


const myVector myPoint::operator-(const myPoint &pt) const{
	float fx = x - pt.x;
	float fy = y - pt.y;
	float fz = z - pt.z;
	return myVector(fx, fy,fz);
}

float myPoint::operator[](const int i) const{
	if(i==0) return x;
	else if(i==1) return y;
	else if(i==2) return z;
	else{
		cerr<<"Point index error!" << endl;
		return 0;
	}
}
