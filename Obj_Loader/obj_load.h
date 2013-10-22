

#ifndef OBJ_LOAD
#define OBJ_LOAD
#include "header.h"

namespace Gova
{
	class ObjLoad
	{
	private:
		ifstream obj;			
		string input;
		char slash;						// To read "/" data from face information( f 1/1/1)
		string line;					// Read the entire line from .obj file
		string first;					// Variable used to read starting string from line

		int i;							// Count used in for loop
		vector<float> vertex;			// Extract and keep the vertex information
		vector<float> texcord;			// Extract and keep the texture cordinates information
		vector<float> normal;			// Extract and keep the normals information
		vector<int> index;			// Extract and keep the index information
				
		GLuint vBuf, tBuf, nBuf, iBuf;		// To keep generated buffer object name which is returned by glGenBuffers(...) 
		GLuint vertexArrayObject;		// To keep generated vertex array object name which is returned by glGenVertexArrays(...)

		float v1,v2,v3,u,v,n1,n2,n3; 
		unsigned int iv,iu,in;		
		bool bTexcordinate, bNormal, bIndex; // Flag to identify whether normal and texture data is available for the .obj file


	public:
		ObjLoad()
		{
			bTexcordinate=false;
			bNormal=false;
			bIndex=false;
		}
		
		//
		//This function is used to Load the .obj file and no index buffer to refer the vertex. 
		//This function  may be usefull to small .obj file
	
		void LoadObjForDrawArrays(char *objFilename);
		
		//
		//This function is used to Load the .obj file and index buffer will be created to refer the vertex information. 
		//
		void LoadObjForDrawElements(char *objFilename);

		//
		// This function is used to allocate the vertex, texture and normal buffer to store the corresponding information to 
		// draw the loaded .obj file.
		//
		void allocate_buffer();

		//
		//This function will set the pointer to pervertex attribute
		//
		void setvertexPointer();

		//
		//Function used to draw the loaded .obj file.
		//
		void draw();
	};
}

#endif