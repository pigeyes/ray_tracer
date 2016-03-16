//
//  p_light.h
//  
//
//  Created by ChuMingChing on 2/16/16.
//
//

#ifndef p_light_h
#define p_light_h

#include <stdio.h>
#include "myPoint.h"
#include "myVector.h"

class p_light{
public:
	p_light(){
		position = myPoint(0.0f, 0.0f, 0.0f);
		color = myVector(0.0f, 0.0f, 0.0f);
	}
	p_light(myPoint pt, myVector rgb):position(pt), color(rgb){}
	myVector getColorVector(){
		return color;
	}
	myPoint getPos(){
		return position;
	}
private:
	myPoint position;
	myVector color;
};

#endif /* p_light_h */
