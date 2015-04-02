#pragma once
#include "GLfiles.h"

struct MeshData
{
	MeshData()
	{
		vertexData = nullptr;
		normalData = nullptr;
		uvData = nullptr;
		//default GL to draw using triangles
		primitiveMode = GL_TRIANGLES;
	}
	~MeshData()
	{
		delete [] vertexData;
		delete [] normalData;
		delete [] uvData;
	}

	GLenum primitiveMode; 
	GLfloat* vertexData;
	GLfloat* normalData;
	GLfloat* uvData;
	//GLint* vertexTriangles;
	//GLint* normalTriangles;
	//GLint* uvTriangles;
	int vertextCount;
	int normalCount;
	int uvCount;
};