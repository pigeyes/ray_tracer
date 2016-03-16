//
//  main.cc
//  
//
//  Created by ChuMingChing on 2/10/16.
//
//
/*
 0 - render original "slow way"
 1 - render bounding boxes "slow way"
 2 - render bounding boxes using BVH
 3 - render normally using BVH
 
 no 3rd arg, render normally using BVH
 */

#include <vector>
#include <iostream>
#include "readscene.h"
#include "camera.h"

using namespace std;


int main (int argc, char *argv[])
{
	try {
		if (argc < 2) {
			cerr << "type in: prog_out scenefilename [mode (0~3)]" << endl;
			return -1;
		}
		
		// global variable or pass by reference?
		// global -> decalred in main
		
		char* inputscene = argv[1];
		char* outputImage = argv[2];
		
		bool useBbox = false;
		bool useBVH = true;
		
		if (argc == 4) {
			if (atoi(argv[3]) == 1) {
				useBbox = true;
				useBVH = false;
			}
			else if (atoi(argv[3]) == 2) {
				useBVH = true;
				useBbox = true;
			}
			else if (atoi(argv[3]) == 3) {
				useBVH = true;
			}
			else if (atoi(argv[0]) == 0) {
				useBVH = false;
			}
			else {
				cerr << "type in: prog_out scenefilename [mode (0~3)]" << endl;
				return -1;
			}
		}

		camera cam;
		vector<surface*> surfacelist;
		// a ghoust pointer that will delete itself after??
		vector<p_light*> pointLights;
		a_light *alPtr = new a_light;
		material *mtrPtr = new material;
		
		readscene readscene;
		readscene.parseSceneFile (inputscene, cam, surfacelist, pointLights, alPtr, mtrPtr);
		
		cam.render (surfacelist, pointLights, alPtr, useBbox, useBVH);
		
		for (auto p:surfacelist){
			delete p;
		}
		surfacelist.clear();
		
		for (auto p:pointLights) {
			delete p;
		}
		pointLights.clear();
		
		cam.writeImage (outputImage);
	}
	
	catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    
	return 0;
}
