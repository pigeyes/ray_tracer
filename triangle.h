#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include"surface.h"
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <limits>

class triangle : public surface{
	public:
		triangle (const myPoint &P1, const myPoint &P2, const myPoint &P3);
		bool intersect(ray* , int, bool useBbox, intersection *&ipoint);
	private:
		myPoint p1;
		myPoint p2;
		myPoint p3;
		myVector normal;
};
#endif