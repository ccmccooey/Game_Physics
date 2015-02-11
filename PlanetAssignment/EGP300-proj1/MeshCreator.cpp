#include "MeshCreator.h"

GLfloat* MeshCreator::convertIndexVertexToGLFloats(Vector3f* vertexArray, int vertArraySize, int *indexArray, int indexArraySize)
{
	int size = 3 * indexArraySize;
	GLfloat* theFloats = new GLfloat[size];

	int counter = 0;
	for (int i = 0; i < indexArraySize; i++)
	{
		theFloats[counter++] = vertexArray[indexArray[i] - 1].x;
		theFloats[counter++] = vertexArray[indexArray[i] - 1].y;
		theFloats[counter++] = vertexArray[indexArray[i] - 1].z;
	}

	return theFloats;
}
GLfloat* MeshCreator::convertIndexVertexFloatToGLFloats(GLfloat* vertexArray, int vertArraySize, int *indexArray, int indexArraySize)
{
	int size = 3 * indexArraySize;
	GLfloat* theFloats = new GLfloat[size];

	for (int i = 0; i < indexArraySize; i++)
	{
		theFloats[i] = vertexArray[indexArray[i] - 1];
	}

	return theFloats;
}
GLfloat* MeshCreator::convertIndexArrayToColorData(int indexArraySize)
{
	int size = 4 * indexArraySize;
	GLfloat* theFloats = new GLfloat[size];

	for (int i = 0; i < size; i++)
	{
		theFloats[i] = 0.5f;

		//this is for alpha
		if ((i + 1) % 4 == 0)
		{
			theFloats[i] = 1.0f;
		}
	}

	return theFloats;
}
GLfloat* MeshCreator::convertIndexArrayToColorData(Color* colorArray, int vertArraySize, int *indexArray, int indexArraySize)
{
	int size = 4 * indexArraySize;
	GLfloat* theFloats = new GLfloat[size];

	int counter = 0;
	for (int i = 0; i < indexArraySize; i++)
	{
		theFloats[counter++] = colorArray[indexArray[i] - 1].R();
		theFloats[counter++] = colorArray[indexArray[i] - 1].G();
		theFloats[counter++] = colorArray[indexArray[i] - 1].B();
		theFloats[counter++] = colorArray[indexArray[i] - 1].A();
	}

	return theFloats;
}


GLfloat* MeshCreator::convertVertsToFloats(Vector3f* vertexArray, int vertArraySize)
{
	int size = vertArraySize * 3;
	GLfloat* theFloats = new GLfloat[size];

	int counter = 0;
	for (int i = 0; i < vertArraySize; i++)
	{
		theFloats[counter] = vertexArray[i].x; 
		counter++;

		theFloats[counter] = vertexArray[i].y; 
		counter++;

		theFloats[counter] = vertexArray[i].z; 
		counter++;
	}

	return theFloats;
}