#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "myVector.h"
#include "myPoint.h"
#include "material.h"

class intersection{
	public:
		intersection():sf_id(-1), t(0.0f){}
		intersection(int SF_ID, float T, const myVector &N, const myVector &V, const myPoint &ITRPT, const material m)
			:sf_id(SF_ID), t(T), n(N), v(V), itrPt(ITRPT), mat(m){}
	//private:
		int sf_id;
		float t;
		myVector n;
		myVector v;
		myPoint itrPt;
		material mat;
};
#endif