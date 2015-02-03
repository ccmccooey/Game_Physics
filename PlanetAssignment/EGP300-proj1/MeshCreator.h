#ifndef _MESHCREATOR_H
#define _MESHCREATOR_H


#include "Vector3f.h"
#include "Color.h"
#include "GLfiles.h"

class MeshCreator
{
public:
	static GLfloat* convertIndexVertexToGLFloats(Vector3f* vertexArray, int vertArraySize, int *indexArray, int indexArraySize);
	static GLfloat* convertIndexArrayToColorData(int indexArraySize);
	static GLfloat* convertIndexArrayToColorData(Color* colorArray, int vertArraySize, int *colorIndexArray, int colorIndexArraySize);
};

#endif