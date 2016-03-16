#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <assert.h> 
#include "readscene.h"
#include "sphere.h"
#include "surface.h"
#include "plane.h"
#include "triangle.h"
#include "camera.h"
#include "myPoint.h"
#include "myVector.h"

using namespace std;

#define IM_DEBUGGING


// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float readscene::getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: the line is not long enough for your token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}

//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//
void readscene::parseSceneFile (char *filnam, camera &cam, vector<surface*> &surfacelist, vector<p_light*>& pointLights, a_light *a_Ptr, material *lastMaterialLoaded)
{
	ifstream in(filnam);
	char buffer[1025];
	string cmd;
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded. 
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.

    
    for (int line=1; in.good(); line++) {   // go through every line in the file until finished
        
		in.getline(buffer,1024);
		buffer[in.gcount()]=0;
		
		cmd="";
		
		istringstream iss(buffer);
		
		iss >> cmd;
		
		if (cmd[0]=='/' or cmd.empty()) {
			// ignore comments or blank lines
			continue;
		}
		else if (cmd=="s")
			
		{    // it's a sphere, load in the parameters
                
                float x, y, z, r;
                iss >> x >> y >> z >> r;

				surface *ms = new sphere(x, y, z, r);
				ms->setMaterial (lastMaterialLoaded);
				surfacelist.push_back(ms);
			
                cout << "got a sphere with ";
                cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
		
			}
		
                
            else if (cmd=="t")   // triangle
			{
				float x1, y1, z1, x2, y2, z2, x3, y3, z3;
				iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
				myPoint p1(x1, y1, z1);
				myPoint p2(x2, y2, z2);
				myPoint p3(x3, y3, z3);
				surface *ps = new triangle(p1, p2, p3);
				ps->setMaterial (lastMaterialLoaded);
				surfacelist.push_back(ps);
				
				cout << "got a triangle with ";
				cout << "parameters: " << x1 << " " << y1 << " " << z1 << " " << endl;
			}
		
            else if (cmd=="p")   // plane
			{
				float nx, ny, nz, d;
				iss >> nx >> ny >> nz >> d;
				myVector normal(nx,ny,nz);
				surface *ps = new plane(normal.getUnitVec(), d);
				ps->setMaterial (lastMaterialLoaded);
				surfacelist.push_back(ps);
				
				//cout << "got a plane with ";
				//cout << "parameters: " << nx << " " << ny << " " << nz << " " << d << endl;
			}

			else if (cmd=="c")
			{
                float x, y, z, vx, vy, vz, d, iw, ih, pw, ph;
				iss >> x >> y >> z >> vx >> vy >> vz >> d >> iw >> ih >> pw >> ph;
				myPoint pos(x, y, z);

				myVector dir(vx, vy, vz);
               	pw = (int) pw;
               	ph = (int) ph;
				
				cam.init(pos, dir, d, iw, ih, pw, ph);

				//cout << "got a camera with ";
				//cout << "parameters: " << x << " " << y << " " << z << " " << vx << " " << vy << " " << vz << " " << d << " " << iw << " " << ih << " " << pw << " " << ph <<endl;
			}
			else if (cmd=="l"){
                
				iss >> cmd;
				if (cmd=="p")   // point light
					{
						float x, y ,z ,r ,g, b;
						iss >> x >> y >> z >> r >> g >> b;
						myPoint pos(x,y,z);
						myVector rgb(r, g, b);
						p_light* plPtr = new p_light(pos, rgb);
						pointLights.push_back(plPtr);
						
						//cout << "got a light with ";
						//cout << "parameters: " << x << " " << y << " " << z << " " << " " << r << " " << g << " " << b << endl;
					}
				else if (cmd=="d"){
					
				}
				else if (cmd=="a")  // ambient light
					{
						float r, g ,b;
						iss >> r >> g >> b;
						a_Ptr->set_alight(r, g, b);
					}
                
			}
            
            //
            // materials:
            //
            else if (cmd=="m")   // material
			{
				// the trick here: we should keep a pointer to the last material we read in,
				// so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
				
				float dr, dg, db, sr, sg, sb, r, ir, ig, ib;
				iss >> dr >> dg >> db>> sr>> sg>> sb>> r>> ir>> ig>> ib;
				lastMaterialLoaded->setMaterial(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
				
				//cout << "got a material with ";
				//cout << "parameters: " << dr << " " << dg << " " << db << " " << sr << " " << sg << " " << sb << " " << r << " " << ir << " " << ig << " " << ib <<endl;
			}
			else if (cmd=="w")
			{
				// alias-wavefront file of triangles
				string aw_file;
				iss >> aw_file;
				std::vector<int> tri_ids;
				std::vector<float> tri_verts;
				readscene::read_wavefront_file(aw_file.c_str(), tri_ids, tri_verts);
				//cout << aw_file.c_str() << endl;
				
				// build all the surfaces:
				for (unsigned int k = 0; k*3 < tri_ids.size(); ++k) {
					myPoint p1(tri_verts[3*tri_ids[3*k]],
							   tri_verts[3*tri_ids[3*k]+1],
							   tri_verts[3*tri_ids[3*k]+2]);
					
					myPoint p2(tri_verts[3*tri_ids[3*k+1]],
							   tri_verts[3*tri_ids[3*k+1]+1],
							   tri_verts[3*tri_ids[3*k+1]+2]);
					
					myPoint p3(tri_verts[3*tri_ids[3*k+2]],
							   tri_verts[3*tri_ids[3*k+2]+1],
							   tri_verts[3*tri_ids[3*k+2]+2]);
					
					surface *ps = new triangle(p1, p2, p3);
					ps->setMaterial (lastMaterialLoaded);
					surfacelist.push_back(ps);
				}
			}
    }
	in.close();
}
//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//
/*
int main (int argc, char *argv[])
{
  
    if (argc != 2) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }

    parseSceneFile (argv[1]);
    
    return 0;
}
*/
void readscene::read_wavefront_file (
								  const char *file,
								  std::vector< int > &tris,
								  std::vector< float > &verts)
{
	
	// clear out the tris and verts vectors:
	tris.clear ();
	verts.clear ();
	
	ifstream in(file);
	char buffer[1025];
	string cmd;
	
	
	for (int line=1; in.good(); line++) {
		in.getline(buffer,1024);
		buffer[in.gcount()]=0;
		
		cmd="";
		
		istringstream iss (buffer);
		
		iss >> cmd;
		
		if (cmd[0]=='#' or cmd.empty()) {
			// ignore comments or blank lines
			continue;
		}
		else if (cmd=="v") {
			// got a vertex:
			
			// read in the parameters:
			double pa, pb, pc;
			iss >> pa >> pb >> pc;
			
			verts.push_back (pa);
			verts.push_back (pb);
			verts.push_back (pc);
		}
		else if (cmd=="f") {
			// got a face (triangle)
			
			// read in the parameters:
			int i, j, k;
			iss >> i >> j >> k;
			
			// vertex numbers in OBJ files start with 1, but in C++ array
			// indices start with 0, so we're shifting everything down by
			// 1
			tris.push_back (i-1);
			tris.push_back (j-1);
			tris.push_back (k-1);
		}
		else {
			std::cerr << "Parser error: invalid command at line " << line << std::endl;
		}
		
	}
	
	in.close();
	
	std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  "
	<< verts.size () / 3.0 << std::endl;
}

