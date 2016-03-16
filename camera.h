//
//  camera.h
//  
//
//  Created by ChuMingChing on 2/10/16.
//
//

#ifndef camera_h
#define camera_h

#include <vector>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include <iostream>
#include <fstream>

#include <cmath>
#include <cstdlib>

#include "myVector.h"
#include "myPoint.h"
#include "ray.h"
#include "surface.h"
#include "sphere.h"
#include "bbox.h"
#include "BVHNode.h"

using namespace Imf;
using namespace std;

class camera{
public:
	
	void init(myPoint pos, myVector dir, float focalLen, float imageW, float imageH, int pixelX, int pixelY);
	ray* genRay(float, float); // intput a pixel address
	bool traceShadowRay(ray* shadRay, const double &tmin, const double &tmax, bool useBbox, const vector<surface*> &surfacelist);
	myVector calPixel(ray*, const vector<surface*>&, const vector<p_light*>&, a_light *alPtr, int recurse_limit, bool useBbox, bool useBVH, BVHNode* root, intersection* ipoint);
	void render(vector<surface*>&, const std::vector<p_light*>&, a_light *alPtr, bool useBbox, bool useBVH);
	void writeImage (const char fileName[]);
	
	// private variable: @style: eye_
	
	myPoint eye;
	float d; // focal length
	myVector u;
	myVector v;
	myVector w;
	float iw; //image size
	float ih;
	int pw; //pixel size
	int ph;
	
	Array2D<Rgba> pixelBuffer; //output image
};

#endif /* camera_h */
