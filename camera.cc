#include "camera.h"
 
/* camera at position [x y z] looking in direction [vx vy vz], with focal length d,
	/ an image plane sized iw by ih (width, height) and number of pixels pw ph
	c x y z vx vy vz d iw ih pw ph
*/ 
 
using namespace std;

void camera::init(myPoint pos, myVector dir, float focalLen, float imageW, float imageH, int pixelX, int pixelY){
	eye = pos;
	d = focalLen;
	iw = imageW;
	ih = imageH;
	pw = pixelX;
	ph = pixelY;
	u = myVector(-dir.dz, 0.0f, dir.dx);
	v = myVector(u.dy*dir.dz-u.dz*dir.dy, u.dz*dir.dx-u.dx*dir.dz, u.dx*dir.dy-u.dy*dir.dx);
	w = myVector(-dir.dx, -dir.dy, -dir.dz);
	u = u.getUnitVec();
	v = v.getUnitVec();
	w = w.getUnitVec();
	
	pixelBuffer.resizeErase(ph, pw);
}

ray* camera::genRay(float xx, float yy){
	float cu = -iw/2.0f+iw*(xx+0.5f)/pw;
	float cv = -ih/2.0f+ih*(ph-yy+0.5f)/ph;
	float dirX= -d*w.dx+cu*u.dx+cv*v.dx;
	float dirY= -d*w.dy+cu*u.dy+cv*v.dy;
	float dirZ= -d*w.dz+cu*u.dz+cv*v.dz;
	myVector dir(dirX, dirY, dirZ);	dir = dir.getUnitVec(); // normalize
	ray* camRay = new ray(eye, dir);
	return camRay;
}

bool camera::traceShadowRay(ray* shadRay, const double &tmin, const double &tmax, bool useBbox, const vector<surface*> &surfacelist)
{
	intersection *ipoint = nullptr;
	
	for (unsigned int i=0; i< (int) surfacelist.size(); ++i)
	{
		if (surfacelist[i]->intersect(shadRay, 0, useBbox, ipoint))
		{
			if (ipoint->t > tmin && ipoint->t < tmax)
				return true;
		}
	}
	
	return false;
	
}

myVector camera::calPixel(ray* rayPtr, const vector<surface*> &surfacelist, const vector<p_light*>& pointLights, a_light *alPtr, int recurse_limit, bool useBbox, bool useBVH, BVHNode* root, intersection* ipoint){
	
	
	if (recurse_limit == 0) return myVector(0.0f, 0.0f, 0.0f);
	
	// check for intersection
	bool isHit = false;
	double tClosest = std::numeric_limits<double>::infinity();
	
	if (useBVH) {
		if (root->intersect(rayPtr, 0, useBbox, ipoint))
			isHit = true;
	}
	else {
		for(unsigned int k=0; k<surfacelist.size(); ++k){ // for each surface in surfacelist
			intersection *i = nullptr;
		
			if(surfacelist[k]->intersect(rayPtr, k, useBbox, i)){
				if (i->t < tClosest){
					tClosest = i->t;
					ipoint = i;
				}
				isHit = true;
			}
		}
	}
	if (!isHit)
		return myVector(0.0f, 0.0f, 0.0f);
	
	// Get the intersection data from the nearest surface
	intersection* data = rayPtr->getNearestData();
	//if (useBVH) {
		data = ipoint;
	//}

	myVector kd = data->mat.getDiffuse();
	myVector ks = data->mat.getSpecular();
	myVector km = data->mat.getIdealSpec();
	
	// ambient light
	myVector Ia = alPtr->getColorVector();
	myVector La = kd*Ia;
	myVector result = La;
	
	// spot light: blinn-phong shadding
	for(size_t i=0; i<pointLights.size(); ++i){
		// generate shadow ray
		myVector shadVec = pointLights[i]->getPos() - data->itrPt;
		float tmax =  shadVec.getNorm();
		shadVec = shadVec.getUnitVec();
		ray* shadRay = new ray(data->itrPt, shadVec);
		bool isblocked = false;
		
		if (useBVH){
			isblocked = traceShadowRay(shadRay, 0.0001, tmax, useBbox, surfacelist);
		}
		else
		{
			for(int j=0; j<(int)surfacelist.size(); ++j){
				if(j!=data->sf_id){
					surfacelist[j]->intersect(shadRay, j, useBbox, ipoint);
				}
			}
		}

		// check for occlusion
		if(shadRay->checkBlock(tmax))
			isblocked = true;
		
		if(isblocked) continue;
		
		// diffuse light
		myVector I = pointLights[i]->getColorVector();
		myVector Ld = kd*I;
		myVector li = pointLights[i]->getPos() - data->itrPt;
		// float length = li.getNorm();
		li = li.getUnitVec();
		float dot1 = data->n.dot(li);
		Ld *= max(dot1,0.0f);
		
		// specular light
		myVector Ls = ks*I;
		myVector h = data->v+li;
		h = h.getUnitVec();
		float dot2 = data->n.dot(h);
		float p = data->mat.getPhongExp();
		Ls *= max(0.0f, pow(dot2, p));
		 
		
		result += Ld+Ls;
		// result /= (length*length);
		// printVector(result);
	}
	if(km[0]==0 && km[1]==0 && km[2]==0)
		return result;
	else{
		myVector reflecDir = data->n * (2.0f * data->n.dot(data->v)) - data->v;
		myPoint reflecPt = data->itrPt + reflecDir * 0.05f;
		ray* reflecRay = new ray(reflecPt, reflecDir);
		return result + km * calPixel(reflecRay, surfacelist, pointLights, alPtr, recurse_limit - 1, useBbox, useBVH, root, ipoint);
	}
}

void camera::render(vector<surface*> &surfacelist, const vector<p_light*>& pointLights, a_light *alPtr, bool useBbox, bool useBVH){
	
	BVHNode* root = nullptr;
	if (useBVH) {
		root = new BVHNode(surfacelist, 0, (int) surfacelist.size(), 0);
		// build tree
	}
	
	// cout << surfacelist.size() << endl;
	for(int j=0; j<ph; ++j){ // for each pixel
		for(int i=0; i<pw; ++i){
			Rgba &px = pixelBuffer[j][i];
			myVector result(0.0f, 0.0f, 0.0f);
			
			ray* currentRay = genRay((float)i-0.5f, (float)j-0.5f);
			intersection* ipoint = nullptr;
			result = calPixel(currentRay, surfacelist, pointLights, alPtr, 5, useBbox, useBVH, root, ipoint);
			// recursive limit: 20
			
			result.getUnitVec();
			
			px.r = result[0];
			px.g = result[1];
			px.b = result[2];
			px.a = 1;
		}
	}
}

void camera::writeImage (const char fileName[]){
	RgbaOutputFile file (fileName, pw, ph, WRITE_RGBA);
	file.setFrameBuffer (&pixelBuffer[0][0], 1, pw);
	file.writePixels (ph);
}
