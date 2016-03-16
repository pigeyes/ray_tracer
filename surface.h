//
//  surface.h
//  
//
//  Created by ChuMingChing on 2/9/16.
//
//

#ifndef surface_h
#define surface_h

#include "myVector.h"
#include "myPoint.h"
#include "ray.h"
#include "p_light.h"
#include "a_light.h"
#include "material.h"
#include "bbox.h"

class surface{
public:
	virtual bool intersect(ray* , int, bool, intersection*&) = 0; // override by subclasses
	void setMaterial(material *mtrPtr){mtr = *mtrPtr;}
	material getMaterial(){return mtr;}
	
	// virtual bool intersect(const Ray &r) const
	// const: this will not modify any private variable in this class
	//        -> useful when using a template
	virtual ~surface(){} // constructor
	
	material mtr;
	bbox box;
	myPoint pos;
};

#endif /* surface_h */
