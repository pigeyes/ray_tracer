//
//  myVector.cc
//  
//
//  Created by ChuMingChing on 2/9/16.
//
//

#include "myVector.h"

using namespace std;

myVector myVector::getUnitVec() const{
	float norm = sqrt(dx*dx+dy*dy+dz*dz);
	return myVector(dx/norm, dy/norm, dz/norm);
}

float myVector::getNorm() const{
	return sqrt(dx*dx+dy*dy+dz*dz);
}

myVector myVector::cross(const myVector &b){
	float x = dy*b.dz - dz*b.dy;
	float y = dz*b.dx - dx*b.dz;
	float z = dx*b.dy - dy*b.dx;
	return myVector(x, y, z);
}

myVector& myVector::operator+=(const myVector &vec){
	dx += vec.dx;
	dy += vec.dy;
	dz += vec.dz;
	return (*this);
}

const myVector myVector::operator+(const myVector &vec) const{
	return myVector(*this)+=vec;
}

myVector& myVector::operator-=(const myVector &vec){
	dx -= vec.dx;
	dy -= vec.dy;
	dz -= vec.dz;
	return (*this);
}

const myVector myVector::operator-(const myVector &vec) const{
	return myVector(*this)-=vec;
}

myVector& myVector::operator*=(const float scale){
	dx *= scale;
	dy *= scale;
	dz *= scale;
	return (*this);
}

const myVector myVector::operator*(const float scale){
	return myVector(*this) *= scale;
}

myVector& myVector::operator/=(const float scale){
	dx /= scale;
	dy /= scale;
	dz /= scale;
	return (*this);
}

const myVector myVector::operator/(const float scale){
	return myVector(*this) /= scale;
}

float myVector::dot(const myVector& rhs){
	return dx*rhs.dx+dy*rhs.dy+dz*rhs.dz;
}

const myVector myVector::operator*(const myVector &vec){
	float x = dx*vec.dx;
	float y = dy*vec.dy;
	float z  = dz*vec.dz;
	return myVector(x,y,z);
}

float myVector::operator[](const int i) const{
	if(i==0) return dx;
	else if(i==1) return dy;
	else if(i==2) return dz;
	else{
		cerr<<"Vector index error!" << endl;
		return 0;
	}
}

void printVector(myVector vec){
	std::cout << vec.dx << " " << vec.dy << " " << vec.dz << std::endl;
}