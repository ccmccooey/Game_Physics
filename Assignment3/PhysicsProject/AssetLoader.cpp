#include "AssetLoader.h"
#include "GraphicsSystem.h"


bool AssetLoader::msLoaded = false;

void AssetLoader::LoadAssets()
{
	if (!msLoaded)
	{
		GraphicsSystem::Instance()->LoadContent();
		msLoaded = true;
	}
}
void AssetLoader::LoadTextures()
{
	
}
void AssetLoader::LoadMaterials()
{

}
void AssetLoader::LoadModels()
{

}