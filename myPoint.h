//
//  myPoint.h
//  
//
//  Created by ChuMingChing on 2/8/16.
//
//

#ifndef myPoint_h
#define myPoint_h

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "myVector.h"

class myPoint{
public:
	myPoint(): x(0.0f), y(0.0f), z(0.0f){}
	myPoint(float xx, float yy, float zz): x(xx), y(yy), z(zz){} //constructor
	myPoint& operator+=(const myVector &vec);
	myPoint& operator-=(const myVector &vec);
	const myPoint operator-(const myVector &vec);
	const myVector operator-(const myPoint &pt) const;
	const myPoint operator+(const myVector &vec);
	
	float operator[](const int i) const;
	
	// float operator[] (const int i) const;
	// friend functions: they don't require istance of class to be called
	// inline: make sure something before operating
	// -> assert();
	// inline double mypoint::operator[]{
	//		assert(there's at least an element in mypoint instance)
	// }
	
	float x;
	float y;
	float z;
};

#endif /* myPoint_h */
