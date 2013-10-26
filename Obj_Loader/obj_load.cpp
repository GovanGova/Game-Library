#include "obj_load.h"

using namespace Gova;
void Gova::ObjLoad::LoadObjForDrawArrays(char *filename)
{
	obj.open(filename,ios::in);
	bool openflag=obj.is_open();
	openflag==true?cout<<endl<<"successfully opend obj file"<<endl:cout<<endl<<"failed to open the input file obj file";
	if(openflag)
	{
		int en=obj.end;
		vector<float> tempVertex;
		vector<float> temptexc;
		vector<float> tempNorm;

		while(!obj.eof())
		{
			getline(obj,line);
			//cout<<endl<<line;
			stringstream ob(line);
			ob>>first;

			if(strcmp(first.data(),"#")==0)
			{
				//skip the comment line
			}
			else if(strcmp(first.data(),"v")==0) 
			{
				ob>>v1>>v2>>v3;

				tempVertex.push_back(v1);
				tempVertex.push_back(v2);
				tempVertex.push_back(v3);
			}
			else if(strcmp(first.data(),"vt")==0) 
			{
				ob>>u>>v;

				temptexc.push_back(u);
				temptexc.push_back(v);
				bTexcordinate=true;

			}		
			else if(strcmp(first.data(),"vn")==0)
			{
				ob>>n1>>n2>>n3;
				tempNorm.push_back(n1);
				tempNorm.push_back(n2);
				tempNorm.push_back(n3);
				bNormal=true;
			}
			else if(strcmp(first.data(),"f")==0)
			{
				if((bNormal!=false)&&(bTexcordinate!=false))
				{
					//1st per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}
					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}

					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}
				}
				else if(bNormal!=false)
				{	//1st per vertex attribute for triangle
					ob>>iv>>slash>>slash>>in;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}

					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>slash>>in;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}

					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>slash>>in;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(in*3)-3;i<(in*3);i++)
					{
						normal.push_back(tempNorm[i]);
					}
				}
				else if(bTexcordinate!=false)
				{
					//1st per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
					
					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
					
					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					for(i=(iu*2)-2;i<(iu*2);i++)
					{
						texcord.push_back(temptexc[i]);
					}
				
				}
				else if((bNormal==false)&&(bTexcordinate==false))
				{
					//1st per vertex attribute for triangle
					ob>>iv;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
					
					//2nd per vertex attribute for triangle
					ob>>iv;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}					
					
					//3rd per vertex attribute for triangle
					ob>>iv;
					for(i=(iv*3)-3;i<(iv*3);i++)
					{
						vertex.push_back(tempVertex[i]);
					}
				}
			}

		}

		printf("\n Finished Loading obj");
	}
	
}
void Gova::ObjLoad::LoadObjForDrawElements(char *filename)
{
	obj.open(filename,ios::in);
	bool openflag=obj.is_open();
	openflag==true?cout<<endl<<"successfully opend obj file"<<endl:cout<<endl<<"failed to open the input file obj file";
	bIndex=true;
	if(openflag)
	{
		int en=obj.end;
		vector<float> tempVertex;
		vector<float> temptexc;
		vector<float> tempNorm;

		while(!obj.eof())
		{
			getline(obj,line);
			//cout<<endl<<line;

			stringstream ob(line);
			ob>>first;

			if(strcmp(first.data(),"#")==0)
			{
				//skip the comment line
			}
			else if(strcmp(first.data(),"v")==0) 
			{
				ob>>v1>>v2>>v3;

				vertex.push_back(v1);
				vertex.push_back(v2);
				vertex.push_back(v3);
			}
			else if(strcmp(first.data(),"vt")==0) 
			{
				ob>>u>>v;

				temptexc.push_back(u);
				temptexc.push_back(v);
				bTexcordinate=true;

			}		
			else if(strcmp(first.data(),"vn")==0)
			{
				ob>>n1>>n2>>n3;
				tempNorm.push_back(n1);
				tempNorm.push_back(n2);
				tempNorm.push_back(n3);
				bNormal=true;
			}
			else if(strcmp(first.data(),"f")==0)
			{
				tempNorm.size()!= normal.size()?normal.resize(vertex.size()):0;
				temptexc.size()!=texcord.size()?texcord.resize(vertex.size()*2/3):0;
				if((bNormal!=false)&&(bTexcordinate!=false))
				{
					//1st per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					index.push_back(iv-1);
					
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];
					
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];


					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					index.push_back(iv-1);
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];
					
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];

					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>iu>>slash>>in;
					index.push_back(iv-1);
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];
					
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];
					
				}
				else if(bNormal!=false)
				{	//1st per vertex attribute for triangle
					//1st per vertex attribute for triangle

					ob>>iv>>slash>>slash>>in;
					if(iv==482)
					{
						printf("");
					}
					index.push_back(iv-1);
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];
					//normal

					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>slash>>in;
					index.push_back(iv-1);
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];

					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>slash>>in;
					index.push_back(iv-1);
					normal[((iv)*3)-3]=tempNorm[((in)*3)-3];
					normal[((iv)*3)-2]=tempNorm[((in)*3)-2];
					normal[((iv)*3)-1]=tempNorm[((in)*3)-1];
				}
				else if(bTexcordinate!=false)
				{
					//1st per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					index.push_back(iv-1);
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];
					

					//2nd per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					index.push_back(iv-1);
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];
					

					//3rd per vertex attribute for triangle
					ob>>iv>>slash>>iu;
					index.push_back(iv-1);
					texcord[((iv)*2)-2]=temptexc[(iu*2)-2];
					texcord[((iv)*2)-1]=temptexc[(iu*2)-1];
					
				
				}
				else if((bNormal==false)&&(bTexcordinate==false))
				{
					//1st per vertex attribute for triangle
					ob>>iv;
					index.push_back(iv-1);
					
					//2nd per vertex attribute for triangle
					ob>>iv;
					index.push_back(iv-1);
					
					//3rd per vertex attribute for triangle
					ob>>iv;
					index.push_back(iv-1);
				}
			}

		}

		printf("\n Finished Loading obj");
	}
	


}

void Gova::ObjLoad:: allocate_buffer()
{
	//Vertex array 
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	
	//Vertex buffer
	glGenBuffers(1,&vBuf);
	glBindBuffer(GL_ARRAY_BUFFER,vBuf);
	glBufferData(GL_ARRAY_BUFFER,vertex.size()*sizeof(float),vertex.data(),GL_DYNAMIC_DRAW);

	//Texture buffer
	if(bTexcordinate==true)
	{
		glGenBuffers(1,&tBuf);
		glBindBuffer(GL_ARRAY_BUFFER,tBuf);
		glBufferData(GL_ARRAY_BUFFER,texcord.size()*sizeof(float),texcord.data(),GL_DYNAMIC_DRAW);
	}

	if(bNormal==true)
	{
		glGenBuffers(1,&nBuf);
		glBindBuffer(GL_ARRAY_BUFFER,nBuf);
		glBufferData(GL_ARRAY_BUFFER,normal.size()*sizeof(float),normal.data(),GL_DYNAMIC_DRAW);
	}
	if(bIndex==true)
	{
		glGenBuffers(1,&iBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iBuf);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,index.size()*sizeof(int),index.data(),GL_DYNAMIC_DRAW);

	}
}
void Gova::ObjLoad::setvertexPointer()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vBuf);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	if(bTexcordinate==true)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER,tBuf);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);
	}
	
	if(bNormal==true)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER,nBuf);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);
	}
	
	glBindVertexArray(0);
}
void Gova::ObjLoad::draw()
{
	glBindVertexArray(vertexArrayObject);
	if(bIndex==true)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iBuf);
		glDrawElements(GL_TRIANGLES,index.size(),GL_UNSIGNED_INT,NULL);
		
	}
	else
	{
		
		glDrawArrays(GL_TRIANGLES,0,(vertex.size()/3));
	}
}