#include "Resources.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Material.h"
#include "MassAggregateModels.h"


Resources::Resources()
{
	mTextures = new TextureManager();

	mTextures->AddTexture(
}
Resources::~Resources()
{

}

MassAggregateModels* Resources::GetModels() const
{

}
TextureManager* Resources::GetTextures() const
{

}
Material* Resources::GetMaterial() const
{

}