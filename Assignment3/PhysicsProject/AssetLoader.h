#ifndef _ASSET_LOADER_H
#define _ASSET_LOADER_H

class AssetLoader
{
private:
	static bool msLoaded;

public:
	static void LoadAssets();

private:
	static void LoadTextures();
	static void LoadMaterials();
	static void LoadModels();
};

#endif