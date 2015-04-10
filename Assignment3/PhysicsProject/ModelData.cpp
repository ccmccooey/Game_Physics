#include "ModelData.h"
#include "MeshData.h"

ModelData::ModelData()
{

}

ModelData::~ModelData()
{	
	unsigned int size = meshList.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete meshList[i];
	}
	meshList.clear();	
}