#include<iostream>
#include<fstream>
#include<string>

#include<vector>
#include<sstream>
#include<math3d.h>
using namespace std;

// There is a static block allocated for loading shaders to 
// prevent heap fragmentation
#define MAX_SHADER_LENGTH   8192


// Bring in OpenGL 
// Windows
#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <gl\glew.h>			// OpenGL Extension "autoloader"
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#endif

// Linux
#ifdef linux
#define GLEW_STATIC
#include <glew.h>
#endif