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
#include "Vector2f.h"
#include "MeshCreator.h"
#include <math.h>
#include <cmath>

#define PI 3.1415926
#define PI_MULT2 PI * 2
#define PI_DIV2 PI / 2


using namespace std;

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
	GLfloat theNormalFloats[] = {0, 0, -1, 0, 0, 1, 1, (GLfloat)-2.98023e-7, 0, (GLfloat)-2.68221e-7, -1, (GLfloat)-1.19209e-7, -1, (GLfloat)2.23517e-7, (GLfloat)-1.3411e-7, (GLfloat)2.38419e-7, 1, (GLfloat)2.08616e-7};

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
void BasicGeometry::setDataToQuad2D(GLBatch* batch)
{
	 BasicGeometry::setDataToQuad(batch, 0, 0, 1, 1, false);
}
void BasicGeometry::setDataToQuad3D(GLBatch* batch)
{
	BasicGeometry::setDataToQuad(batch, 0, 0, 1, 1, true);
}
void BasicGeometry::setDataToQuad(GLBatch* batch, float uvX, float uvY, float uvW, float uvH, bool originCenter)
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
	if (originCenter)
	{
		verts[0] = Vector3f(-0.5f, -0.5f, z);
		verts[1] = Vector3f(-0.5f, 0.5f, z);
		verts[2] = Vector3f(0.5f, 0.5f, z);
		verts[3] = Vector3f(0.5f, -0.5f, z);
	}
	else
	{
		verts[0] = Vector3f(0, -1, z);
		verts[1] = Vector3f(0, 0, z);
		verts[2] = Vector3f(1, 0, z);
		verts[3] = Vector3f(1, -1, z);
	}

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
	//The math is beyond my capability of understanding. I had to use an internet source for the code to generate it, I made some modifications to support the architecture
	//http://stackoverflow.com/questions/7946770/calculating-a-sphere-in-opengl

	float radius = 1.0f;
	unsigned int rings = 9;
	unsigned int sectors = 9;


	const float R = 1.0f / (float)(rings - 1);
	const float S = 1.0f / (float)(sectors - 1);
	unsigned int r, s;

	int vertsCount = rings * sectors;
	Vector3f* verts = new Vector3f[vertsCount];

	int normalsFloatCount = rings * sectors * 3;
	GLfloat* normals = new GLfloat[normalsFloatCount];

	int uvFloatCount = rings * sectors * 2;
	GLfloat* uvs = new GLfloat[uvFloatCount];
	
	
	int t = 0;
	//t = uvFloatCount - 1;
	//int v = 0;
	
	int vCounter = 0; //verts
	int nCounter = 0; //normals
	
	for (r = 0; r < rings; r++)
	{
		for (s = 0; s < sectors; s++)
		{
			float const y = sinf((float)-PI_DIV2 + (float)PI * r * R);
			float const x = cosf(2 * (float)PI * s * S) * sin((float)PI * r * R);
			float const z = sinf(2 * (float)PI * s * S) * sin((float)PI * r * R);

			uvs[t] = (float)s * S; 
			t++;
			
			uvs[t] = (float)r * R;
			t++;
			
			//uvs[t] = (float)r * R; t--;
			//uvs[t] = (float)s * S; t--;

			verts[vCounter] = Vector3f(x * radius, y * radius, z * radius);
			//= x * radius;
			//*v++ = y * radius;
			//*v++ = z * radius;

			normals[nCounter] = x; nCounter++;
			normals[nCounter] = y; nCounter++;
			normals[nCounter] = z; nCounter++;
			
			vCounter++;
		}
	}

	int indexCount = (rings - 1) * (sectors - 1) * 4;
	int* indicies = new int[indexCount]; //4 for quads
	int i = 0;

	for (r = 0; r < rings - 1; r++)
	{
		for (s = 0; s < sectors -1 ; s++) 
		{

			indicies[i] = r * sectors + s;
			indicies[i] += 1;
			i++; 

			indicies[i] = r * sectors + (s + 1);
			indicies[i] += 1;
			i++;					

			indicies[i] = (r + 1) * sectors + (s + 1);
			indicies[i] += 1;
			i++;

			indicies[i] = (r + 1) * sectors + s;
			indicies[i] += 1;
			i++;

			/*
			indicies[i] = r * sectors + s;
			indicies[i] += 1;
			i++; 

			indicies[i] = r * sectors + (s + 1);
			indicies[i] += 1;
			i++;

			indicies[i] = (r + 1) * sectors + (s + 1);
			indicies[i] += 1;
			i++;

			indicies[i] = (r + 1) * sectors + s;
			indicies[i] += 1;
			i++;*/
		}
	}

	//reverse it
	/*
	int ub = indexCount - 1;
	int lb = 0;
	int dif = ub - lb;
	int tmp;

	while (dif > 0)
	{
		tmp = indicies[lb];
		indicies[lb] = indicies[ub];
		indicies[ub] = tmp;
		ub--;
		lb++;

		dif = ub - lb;
	}*/


	//GLfloat* vertsF = MeshCreator::convertVertsToFloats(verts, vertsCount);
	//GLfloat* theVertFloats = MeshCreator::convertIndexVertexFloatToGLFloats(vertsF, vertsCount, indicies, indexCount);

	GLfloat* theVertFloats = MeshCreator::convertIndexVertexToGLFloats(verts, vertsCount, indicies, indexCount);

	//copy the data
	batch->Begin(GL_QUADS, (GLint)indexCount, 1);
	batch->CopyVertexData3f(theVertFloats);
	batch->CopyNormalDataf(normals);
	batch->CopyTexCoordData2f(uvs, 0);
	batch->End();

	//delete the data
	delete[] verts;
	delete[] indicies;
	delete[] normals;
	delete[] theVertFloats;
	delete[] uvs;

	//delete [] vertsF;
}

/*
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

	int indexCount = 8;
	int indexArray[] =
	{
		1, 2, 3,
		2, 3, 4,
		3, 4, 5,
		4, 5, 6,
		5, 6, 7,
		6, 7, 8,
		7, 8, 9,
		8, 9, 10
	};

	GLfloat theUVFloats[] = { 0, 0, 0, 1, 1, 0, 1, 1};

	//convert the verticies and indicies information to a glfloat array
	GLfloat* theVertFloats = MeshCreator::convertIndexVertexToGLFloats(verts, vertsCount, indexArray, indexCount);


	//copy the data
	batch->Begin(GL_QUADS, (GLint)indexCount, 1);
	batch->CopyVertexData3f(theVertFloats);
	batch->End();


	//delete the data
	delete [] verts;
}*/

