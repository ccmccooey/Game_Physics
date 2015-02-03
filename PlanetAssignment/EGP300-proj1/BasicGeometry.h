/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  BasicGeometry.h
*
*	Description:
*		This is a static class that is used to create some basic 3D geometry such as a cube, sphere, quad, ect.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _BASIC_GEOMETRY
#define _BASIC_GEOMETRY

#include "GLfiles.h"
#include "Vector3f.h"

class BasicGeometry
{
public:
	static void setDataToCube(GLBatch* mesh);
	static void setDataToCube(GLBatch* mesh, Vector3f relativeSpace);
	static void setDataToQuad(GLBatch* mesh);
	static void setDataToQuad(GLBatch* batch, float uvX, float uvY, float uvW, float uvH);
	static void setDataToSphere(GLBatch* mesh);
};

#endif