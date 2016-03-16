//
//  ray.h
//  
//
//  Created by ChuMingChing on 2/8/16.
//
//

#ifndef ray_h
#define ray_h

#include <vector>
#include "myVector.h"
#include "myPoint.h"
#include "intersection.h"

using namespace std;

class ray{
public:
	ray(const myPoint &pt, const myVector &vec):pos(pt), dir(vec.getUnitVec()){}
	ray(const myPoint &pt1,const myPoint &pt2):pos(pt1), dir(pt1-pt2){
		dir = dir.getUnitVec();
	}
	void addIntersection(intersection* data){
		intersections.push_back(data);
	}
	intersection* getNearestData(){
		float tret = intersections[0]->t;
		int k = 0;
		for(unsigned int i=1; i<intersections.size(); i++){
			if(tret > intersections[i]->t){
				tret = intersections[i]->t;
				k = i;
			}
		}
		return intersections[k];
	}
	bool checkBlock(float tmax){
		if(intersections.empty())return false;
		else{
			for(size_t i=0; i<intersections.size(); ++i){
				if(intersections[i]->t<tmax)
					return true;
			}
			return false;
		}
	}
	
	vector<intersection*> getData(){return intersections;}
	myPoint getPos(){return pos;}
	myVector getDir(){return dir;}

	myPoint pos;
	myVector dir;
	vector<intersection*> intersections;
};


#endif /* ray_h */
