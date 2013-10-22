Game-Library
============

This library used to load the model form obj file and load the terrain.


Obj Loader:
-----------

Obj_loader.cpp and Obj_loader.h are used to load the obj model from .obj file. Please find the following restriction

1. Kindly the import the obj file in blender if that obj file faces are not arranged trinagles
2. It will extract only the vertex, texture cordinate and normal from obj file and it will not load the .mtl file. So expected output will not have color and texture mapped model
3. Order of API call should be like below
	
	a)	void LoadObjForDrawArrays(char *objFilename); // data will be arraged in the format which will be used by "glDrawArrays(...)
		(OR)
		void LoadObjForDrawElements(char *objFilename); // data will be arraged in the format which will be used by "glDrawElements(...).
														// This function currently will extract only vertext position. extracting all the data will be implemented
			
	b)	void allocate_buffer();
	C)	void setvertexPointer();
	D)	void draw(); //This should be called in while loop
4. It is not provide shader part. User have to create the shader to render the model.
-----------

Terrain Loader
------------
Readme for terrain.h and terrain.cpp will be updated soon.
------------


