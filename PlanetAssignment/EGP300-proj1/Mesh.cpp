/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Mesh.cpp
*
*	Description:
*		This class stores the OpenGL batches used to define geometry.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Mesh.h"
#include "BasicGeometry.h"

Mesh::Mesh()
{
	mBatch = new GLBatch();
}
Mesh::Mesh(Geometry geometryType)
{
	mBatch = new GLBatch();
	if (geometryType == Geometry::CUBE)
	{
		BasicGeometry::setDataToCube(mBatch);
		
	}
	if (geometryType == Geometry::QUAD)
	{
		BasicGeometry::setDataToQuad(mBatch);
		
	}
}

Mesh::~Mesh()
{
	delete mBatch;
}

void Mesh::Draw()
{
	mBatch->Draw();
}


