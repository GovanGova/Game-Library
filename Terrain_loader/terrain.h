#ifndef TERRAIN_H
#define TERRAIN_H

#include<GLTools.h>
#include<iostream>
#include<cassert>
#include<cmath>
using namespace std;
namespace Gova 
{
	class terrain
	{
	private:
		int Height, Width;
		unsigned char *data;
		M3DVector3f *vertex;
		M3DVector2f *texcord;
		M3DVector4f *color;
		int iSize, iIndexbufsize, halfterrainWidth, halfterrainHeight;
		GLuint vBuf,indexBuf, TextureBuf,ColorBuf;
		GLuint vertexArrayObject;
		GLuint* indexbuffer;

		
		void Delete_Buffer(GLuint& id);
		void createVertexBuf();
		void createTextureBuf();
		void createColorBuf();
		void createIndexBuffer();
		void GetIndexBuffer();
	public:
		terrain();
		terrain(int width, int height);
		void getHeightAtEyePos(M3DVector3f& vector);
		void allocate_buffer(GLuint& id);
		void loadFromRaw(char *ptr, int bitsperpixel=8);
		void setvertexPointer();
		void draw();
		
		//It willsupport only 8 bit per pixel
		float getHeight(unsigned char* data, int numSize=1);
		~terrain();
	};
}

#endif