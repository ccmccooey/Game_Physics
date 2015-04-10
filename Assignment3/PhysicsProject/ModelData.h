#pragma once
#include <vector>
struct MeshData;

struct ModelData
{
	ModelData();
	~ModelData();
	
	std::vector<MeshData*> meshList;
};