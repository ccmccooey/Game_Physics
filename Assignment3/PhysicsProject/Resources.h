#ifndef _GRAPHICS_SYSTEM_H
#define _GRAPHICS_SYSTEM_H

#include <vector>

class Model;
class TextureManager;
class Material;
class MassAggregateModels;

class Resources
{
private:
	TextureManager* mTextures;
	Material* mMaterial;
	MassAggregateModels* mModels;

public:
	Resources();
	~Resources();

	MassAggregateModels* GetModels() const;
	TextureManager* GetTextures() const;
	Material* GetMaterial() const;
};

#endif