//
//  material.h
//  
//
//  Created by ChuMingChing on 2/16/16.
//
//

#ifndef material_h
#define material_h

#include <stdio.h>
#include "myVector.h"
#include "myPoint.h"

class material{
public:
	material():dr(0.0f), dg(0.0f), db(0.0f), sr(0.0f), sg(0.0f), sb(0.0f),
	r(0.0f), ir(0.0f), ig(0.0f), ib(0.0f){} //constructor
	myVector getDiffuse(){
		return myVector(dr,dg,db);
	}
	myVector getSpecular(){
		return myVector(sr, sg, sb);
	}
	myVector getIdealSpec(){
		return myVector(ir, ig, ib);
	}
	float getPhongExp(){
		return r;
	}
	void setMaterial(float DR, float DG, float DB, float SR, float SG, float SB, float R, float IR, float IG, float IB){
		dr = DR; dg = DG; db = DB;
		sr = SR; sg = SG; sb = SB; r= R;
		ir = IR; ig = IG; ib = IB;
	}
private:
	float dr, dg, db, sr, sg, sb, r, ir, ig, ib;
};

#endif /* material_h */
