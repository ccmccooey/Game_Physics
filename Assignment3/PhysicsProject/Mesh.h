/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Mesh.h
*
*	Description:
*		This class stores the OpenGL batches used to define geometry.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MESH_H
#define _MESH_H

#include "GLfiles.h"
#include "Geometry.h"


class Mesh
{
private:
	GLBatch* mBatch;

public:
	Mesh();
	Mesh(Geometry geometryType);
	~Mesh();
	void Draw();

};

#endif