#include "terrain.h"


Gova::terrain::terrain()
{

}

Gova::terrain::~terrain()
{
	Height=0;
	Width=0;
	delete[] vertex;
	delete[] texcord;
	delete[] color;
}

Gova::terrain::terrain(int width, int height)
{
	iSize=width*height;
	data=new unsigned char[iSize];
	Height=height;
	Width=width;
	vertex=new M3DVector3f[iSize];
	texcord=new M3DVector2f[iSize];
	color=new M3DVector4f[iSize];
}

//It willsupport only 8 bit per pixel
float Gova::terrain::getHeight(unsigned char* data,int numBytes)
{
	if(numBytes==1)
	{
		return (unsigned char)(data[0]) / (float)0xff;
	}
	return 0;
}

void Gova::terrain::loadFromRaw(char* rawFile,int bitPerPixel)
{
	assert(rawFile!=NULL);
	FILE *fp=fopen(rawFile,"rb");
	if(fp==NULL)
	{
		cout<<"File is not valid";
	}
	int result=fread(data,1,iSize,fp);
	if(result!=iSize)
	{
		cout<<"Fail to read the data from the file"<<endl;
		exit(0);
	}
	int terrainwidth=(Width-1)*.01;
	int terrainHeight=(Height-1)*.01;
	int bytesperPixel=bitPerPixel/8;
	halfterrainWidth=(Width-1)/2;
	halfterrainHeight=(Height-1)/2;
	for(int i=0;i<Height;i++)
	{
		for(int j=0; j<Width;j++)
		{
			M3DVector3f tempVert;
			int index=i*Width+j;
			//Vertex position
			float x=j-halfterrainWidth;
			unsigned char testdata=data[index];
			float y=(getHeight(&data[index]))*100;

			float z=i-halfterrainHeight;
			m3dLoadVector3(vertex[index],x,y,z);
			float s=((float)i/(float)(Height-1));
			float t=((float)j/(float)(Width-1));

			m3dLoadVector2(texcord[index],s,t);
			/*GLfloat *tex=(GLfloat*)texcord;
			cout<<"texcord"<<tex[index*2]<<"\t"<<tex[(index*2)+1]<<endl;*/


		}
	}
	GetIndexBuffer();
	createVertexBuf();
	createTextureBuf();
	createColorBuf();
	createIndexBuffer();
	setvertexPointer();

}

void Gova::terrain::allocate_buffer(GLuint& id)
{
	glGenBuffers(1, &id);
	/*glBindVertexArray(id);
	glGenBuffers(1,&vBuf);
	glBindBuffer(GL_ARRAY_BUFFER,vBuf);
	glBufferData(GL_ARRAY_BUFFER,iSize*12,vertex,GL_DYNAMIC_DRAW);

	*/
}

void Gova::terrain::setvertexPointer()
{
	glGenVertexArrays(1,&vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER,vBuf);
	glVertexAttribPointer(GLT_ATTRIBUTE_VERTEX,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,TextureBuf);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindVertexArray(0);

}
void Gova::terrain::draw()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuf);
	glDrawElements(GL_TRIANGLES,iIndexbufsize,GL_UNSIGNED_INT,0);
}

void Gova::terrain::GetIndexBuffer()
{
	int numTriangles=(Width-1)*(Height-1)*2;
	iIndexbufsize=numTriangles*3;
	indexbuffer=new GLuint[iIndexbufsize];
	int count=0;
	for(int j=0;j<(Height-1);++j)
	{
		for(int i=0;i<(Width-1);++i)
		{
			int vertexindex= (j*Width)+i;
			indexbuffer[count++]=vertexindex;
			indexbuffer[count++]=vertexindex+(Width)+1;
			indexbuffer[count++]=vertexindex+1;

			//Bottom triangle
			indexbuffer[count++]=vertexindex;
			indexbuffer[count++]=vertexindex+(Width);
			indexbuffer[count++]=vertexindex+(Width)+1;

		}
	}

}
void Gova::terrain::createVertexBuf()
{
	allocate_buffer(vBuf);
	glBindBuffer(GL_ARRAY_BUFFER,vBuf);
	glBufferData(GL_ARRAY_BUFFER,iSize*12,vertex,GL_DYNAMIC_DRAW);
}
void Gova::terrain::createTextureBuf()
{
	allocate_buffer(TextureBuf);
	glBindBuffer(GL_ARRAY_BUFFER,TextureBuf);
	glBufferData(GL_ARRAY_BUFFER,iSize*8,texcord,GL_DYNAMIC_DRAW);
}
void Gova::terrain::createColorBuf()
{
	allocate_buffer(ColorBuf);
	glBindBuffer(GL_ARRAY_BUFFER,ColorBuf);
	//glBufferData(GL_ARRAY_BUFFER,iSize*4,texcord,GL_DYNAMIC_DRAW);
}
void Gova::terrain::createIndexBuffer()
{
	allocate_buffer(indexBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,iIndexbufsize*4,&indexbuffer[0],GL_DYNAMIC_DRAW);
}
void Gova::terrain::Delete_Buffer(GLuint& id)
{
	glDeleteBuffers(1,&id);
}

void Gova::terrain::getHeightAtEyePos(M3DVector3f& eyePos)
{
	GLfloat yAt, yAtd;
	if((abs(eyePos[2])>halfterrainHeight)||(abs(eyePos[0])>halfterrainHeight))
	{
		
	}
	else
	{
	/*since the height map is mapped to ([-width/2 to width/2],y,[height/2 to height/2]). we need to map the incomming x,z values accordingly*/
	int index=(Width*(halfterrainHeight-eyePos[2]))+(halfterrainWidth +eyePos[0]);
	yAt=data[index];
	/*if((abs(halfterrainWidth +eyePos[0]+10))<halfterrainWidth)
	{
		int indexatd=((halfterrainHeight-eyePos[2])+5)+(halfterrainWidth +eyePos[0]+10);
		yAtd=data[index]
	} */
	
	eyePos[1]=yAt+10;
	}
}