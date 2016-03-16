
#ifndef BVHNode_h
#define BVHNode_h

#include <iostream>
#include "bbox.h"
#include "surface.h"
#include "myVector.h"
#include "myPoint.h"

#include <vector>
#include <algorithm>
using namespace std;
#include <queue>
#include <utility>


class BVHNode : public surface {

public:

	bool static compareX (const surface* lhs, const surface* rhs) {
		float l = (lhs->box.min.x + lhs->box.max.x) / 2;
		float r = (rhs->box.min.x + rhs->box.max.x) / 2;
		return (l < r);
	};
	bool static compareY (const surface* lhs, const surface* rhs) {
		float l = (lhs->box.min.y + lhs->box.max.y) / 2;
		float r = (rhs->box.min.y + rhs->box.max.y) / 2;
		return (l < r);
	};
	bool static compareZ (const surface* lhs, const surface* rhs) {
		float l = (lhs->box.min.z + lhs->box.max.z) / 2;
		float r = (rhs->box.min.z + rhs->box.max.z) / 2;
		return (l < r);
	};

	BVHNode(vector<surface*> surfacelist, int start, int end, int axis) {
		//cout << "a node" << endl;
		if (end - start == 1) {
			left = surfacelist[start];
			box = surfacelist[start]->box;
		}
		else if (end - start == 2) {
			left = surfacelist[start];
			right = surfacelist[start+1];
			float minx = min(left->box.min[0], right->box.min[0]);
			float miny = min(left->box.min[1], right->box.min[1]);
			float minz = min(left->box.min[2], right->box.min[2]);
			float maxx = max(left->box.max[0], right->box.max[0]);
			float maxy = max(left->box.max[1], right->box.max[1]);
			float maxz = max(left->box.max[2], right->box.max[2]);
			box.min = myPoint(minx, miny, minz);
			box.max = myPoint(maxx, maxy, maxz);
		}
		else {
			if (axis == 1) {
				sort(surfacelist.begin(), surfacelist.end(), compareX);
			}
			else if (axis == 2) {
				sort(surfacelist.begin(), surfacelist.end(), compareY);
			}
			else {
				sort(surfacelist.begin(), surfacelist.end(), compareZ);
			}
			left = new BVHNode(surfacelist, start, start + ((end - start) / 2) + 1, (axis+1) % 3);
			right = new BVHNode(surfacelist, start + ((end - start) / 2), end, (axis+1) % 3);
			float minx = min(left->box.min[0], right->box.min[0]);
			float miny = min(left->box.min[1], right->box.min[1]);
			float minz = min(left->box.min[2], right->box.min[2]);
			float maxx = max(left->box.max[0], right->box.max[0]);
			float maxy = max(left->box.max[1], right->box.max[1]);
			float maxz = max(left->box.max[2], right->box.max[2]);
			box.min = myPoint(minx, miny, minz);
			box.max = myPoint(maxx, maxy, maxz);
		}
	};
	
	virtual bool intersect(ray* rayPtr, int sf_id, bool useBbox, intersection *&rec) {
		//cout << "hi" << endl;
		float intersectionT;
		if (!box.intersect(rayPtr, intersectionT))
			return false;
		intersection* lrec = nullptr;
		intersection* rrec = nullptr;
		bool left_hit = false;
		bool right_hit = false;
		if (left != NULL) {
			left_hit = left->intersect(rayPtr, sf_id, useBbox, lrec);
		}
		if (right != NULL) {
			right_hit = right->intersect(rayPtr, sf_id, useBbox, rrec);
		}
		
		if (left_hit && right_hit) {
			if (lrec->t < rrec->t) {
				rec = lrec;
			}
			else
				rec = rrec;
			return true;
		}
		else if (left_hit) {
			rec = lrec;
			return true;
		}
		else if (right_hit) {
			rec = rrec;
			return true;
		}
		else return false;
	}
	
	surface* left;
	surface* right;
};

#endif