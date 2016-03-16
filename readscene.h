//
//  readscene.h
//  
//
//  Created by ChuMingChing on 2/9/16.
//
//

#ifndef readscene_h
#define readscene_h

#include <string>
#include <vector>
#include "camera.h"
#include "surface.h"
#include "p_light.h"
#include "a_light.h"
#include "material.h"


using namespace std;
class readscene {
public:
float getTokenAsFloat (string inString, int whichToken);
const char* getFileName (string inString);
void parseSceneFile (char *fname, camera &cam, vector<surface*> &surfacelist, vector<p_light*>&,  a_light *a_Ptr, material*);
void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< float > &verts);

};
#endif /* readscene_h */
