/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  BasicGeometry.cpp
*
*	Description:
*		This is a static class that is used to create some basic 3D geometry such as a cube, sphere, quad, ect.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "BasicGeometry.h"
#include "GLFiles.h"
#include "Vector3f.h"
#include "MeshCreator.h"
#include <math.h>

void BasicGeometry::setDataToCube(GLBatch* batch)
{
	BasicGeometry::setDataToCube(batch, Vector3f::zero);
}
void BasicGeometry::setDataToCube(GLBatch* batch, Vector3f relativeSpace)
{
	int vertsCount = 8;
	Vector3f* verts = new Vector3f[vertsCount];	
	float x = 0.5f;
	float y = 0.5f;
	float z = 0.5f;

	//verticies	
	verts[0] = Vector3f(x, -y, -z);
	verts[1] = Vector3f(x, -y, z);
	verts[2] = Vector3f(-x, -y, z);
	verts[3] = Vector3f(-x, -y, -z);
	verts[4] = Vector3f(x, y, -z);
	verts[5] = Vector3f(x, y, z);
	verts[6] = Vector3f(-x, y, z);
	verts[7] = Vector3f(-x, y, -z);

	//indicies using quads
	int indexCount = 24;
	int indexArray[] = 
	{ 
		1, 2, 3, 4, 
		5, 8, 7, 6, 
		1, 5, 6, 2, 
		2, 6, 7, 3, 
		3, 7, 8, 4, 
		5, 1, 4, 8 
	};

	//convert the verticies and indicies information to a glfloat array
	GLfloat* theVertFloats = MeshCreator::convertIndexVertexToGLFloats(verts, vertsCount, indexArray, indexCount);

	//convert the indicies to make colors for geometry that does not use textures
	GLfloat* theColorFloats = MeshCreator::convertIndexArrayToColorData(indexCount);

	//create the normals
	GLfloat theNormalFloats[] = {0, 0, -1, 0, 0, 1, 1, -2.98023e-7, 0, -2.68221e-7, -1, -1.19209e-7, -1, 2.23517e-7, -1.3411e-7, 2.38419e-7, 1, 2.08616e-7};

	//create the uvs
	GLfloat theUVFloats[] = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
		0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1};

	//copy the data
	batch->Begin(GL_QUADS, (GLint)indexCount, 1);
	batch->CopyVertexData3f(theVertFloats);
	batch->CopyColorData4f(theColorFloats);
	batch->CopyNormalDataf(theNormalFloats);
	batch->CopyTexCoordData2f(theUVFloats, 0);
	batch->End();

	//delete the data
	delete[] verts;
	delete[] theVertFloats;
	delete[] theColorFloats;
	//delete[] normals;
}
void BasicGeometry::setDataToQuad(GLBatch* batch)
{
	 BasicGeometry::setDataToQuad(batch, 0, 0, 1, 1);
}
void BasicGeometry::setDataToQuad(GLBatch* batch, float uvX, float uvY, float uvW, float uvH)
{
	int vertsCount = 4;
	Vector3f* verts = new Vector3f[vertsCount];	
	float x = 0.5f;
	float y = 0.5f;
	float z = 0.0f;

	//verticies
	//centered
	/*
	verts[0] = Vector3f(-x, y, z);
	verts[1] = Vector3f(-x, -y, z);
	verts[2] = Vector3f(x, -y, z);
	verts[3] = Vector3f(x, y, z);*/

	verts[0] = Vector3f(0, -1, z);
	verts[1] = Vector3f(0, 0, z);
	verts[2] = Vector3f(1, 0, z);
	verts[3] = Vector3f(1, -1, z);

	//quads	
	int indexCount = 4;
	int indexArray[] = 
	{ 
		1, 2, 3, 4		
	};

	//convert the verticies and indicies information to a glfloat array
	GLfloat* theVertFloats = MeshCreator::convertIndexVertexToGLFloats(verts, vertsCount, indexArray, indexCount);

	//convert the indicies to make colors for geometry that does not use textures
	GLfloat* theColorFloats = MeshCreator::convertIndexArrayToColorData(indexCount);

	//create the normals
	GLfloat theNormalFloats[] = {0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1};

	//create the uvs
	GLfloat theUVFloats[] = 
	{
		uvX, uvY + uvH,
		uvX, uvY,
		uvX + uvW, uvY,
		uvX + uvW, uvY + uvH
		
		
	};

	//copy the data
	batch->Begin(GL_QUADS, (GLint)indexCount, 1);
	batch->CopyVertexData3f(theVertFloats);
	batch->CopyColorData4f(theColorFloats);
	batch->CopyNormalDataf(theNormalFloats);
	batch->CopyTexCoordData2f(theUVFloats, 0);
	batch->End();

	//delete the data
	delete[] verts;
	delete[] theVertFloats;
	delete[] theColorFloats;
}


void BasicGeometry::setDataToSphere(GLBatch* batch)
{
	float radius = 1.0f;

	// Iterate through phi, theta then convert r,theta,phi to  XYZ		
	Vector3f vert;

	float piDiv10 = M3D_PI / 10.0;

	int vertsCount = powf((M3D_2PI / piDiv10), 2);

	Vector3f* verts = new Vector3f[vertsCount];	
	int counter = 0;
	for (double phi = 0.0; phi < M3D_2PI; phi += piDiv10) // Azimuth [0, 2PI]
    {
        for (double theta = 0.0; theta < M3D_PI; theta += piDiv10) // Elevation [0, PI]
        {
            
			vert = Vector3f();

            vert.x = radius * cosf(phi) * sinf(theta);
            vert.y = radius * sinf(phi) * sinf(theta);
            vert.z = radius             * cosf(theta);
            verts[counter] = vert;
			counter++;
        }
    }

	//convert the verticies and indicies information to a glfloat array
	//GLfloat* theVertFloats = MeshCreator::convertIndexVertexToGLFloats(verts, vertsCount, indexArray, indexCount);


	//copy the data
	//batch->Begin(GL_QUADS, (GLint)indexCount, 1);
	//batch->CopyVertexData3f(theVertFloats);
	//batch->End();


	//delete the data
	delete [] verts;
}

