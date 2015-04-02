#include "Level.h"
#include "ObjectSpawner.h"
#include "MassAggregateGeometry.h"
#include <fstream>
#include <queue>
#include <iostream>

using namespace std;

//convert geometry type
MassAggregateGeometry charToGeo(char c)
{
	MassAggregateGeometry type;
	switch(c)
	{
	case 'o':
		type = MassAggregateGeometry::MA_Point;
		break;
	case 'l':
		type = MassAggregateGeometry::MA_Solid_Line;
		break;
	case 'c':
		type = MassAggregateGeometry::MA_Solid_Cube;
		break;
	case 't':
		type = MassAggregateGeometry::MA_Solid_Tetrahedron;
		break;
	case 'p':
		type = MassAggregateGeometry::MA_Solid_PyramidWithTop;
		break;
	default:
		type = MassAggregateGeometry::MA_Point;
		break;
	}
	return type;
}

//load the level
bool Level::LoadLevel(const std::string &dataFile, ObjectSpawner* spawner)
{
	ifstream reader = ifstream();
	queue<LNode*> instructions;

	reader.open(dataFile);

	if (reader.fail())
	{
		cerr << "ERROR: Level data file (" << dataFile << ") was not found." << endl;
		return false;
	}
	float x, y, z;
	instructions = queue<LNode*>();

	//get instructions from text file
	while (!reader.eof())
	{
		LNode* node = new LNode();
		
		reader >> node->type >> x >> y >> z;
		node->position = Vector3f(x, y, z);
		instructions.push(node);
	}

	//read instructions
	LNode* obj;
	while (instructions.size() > 0)
	{
		obj = instructions.front();
		spawner->SpawnObject(obj->position, charToGeo(obj->type));
		delete obj;
		instructions.pop();
	}

	reader.close();
	return true;
}