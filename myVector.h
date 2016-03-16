//
//  myVector.h
//  
//
//  Created by ChuMingChing on 2/9/16.
//
//

#ifndef myVector_h
#define myVector_h

#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

class myVector{
public:
	myVector(float x=0.0f, float y=0.0f, float z=0.0f): dx(x), dy(y), dz(z){} //constructor
	float dot(const myVector& rhs);
	myVector cross(const myVector&);
	myVector getUnitVec() const;
	float getNorm() const;
	const myVector operator+(const myVector &vec) const;
	myVector& operator+=(const myVector &vec);
	const myVector operator-(const myVector &vec) const;
	const myVector operator*(const myVector &vec);
	const myVector operator/(const float scale);
	myVector& operator-=(const myVector &vec);
	myVector& operator*=(const float scale);
	const myVector operator*(const float scale);
	myVector& operator/=(const float scale);
	float operator[](const int i) const;
	
	friend void printVector(myVector vec);
	
	float dx;
	float dy;
	float dz;
};

#endif /* myVector_h */
