/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  TextureManager.cpp
*
*	Description:
*		This class manages textures.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "TextureManager.h"
#include "Texture.h"

//constructors
TextureManager::TextureManager()
{
	mTextureMap = map<string, Texture*>();
}
TextureManager::~TextureManager()
{
	RemoveAllTextures();
}

//removing the textures
void TextureManager::RemoveAllTextures()
{
	map<string, Texture*>::iterator iter = mTextureMap.begin();
	map<string, Texture*>::iterator back = mTextureMap.end();

	while (iter != back)
	{
		Texture* texture = iter->second;
		delete texture;
		iter->second = nullptr;
		iter++;
	}

	mTextureMap.clear();
}

//adding new textures
bool TextureManager::AddTexture(const string &filepath) //add a single texture and use the filepath as the key
{
	return AddTexture(filepath, filepath);
}
bool TextureManager::AddTexture(const string &filepath, const string &customKey) //add a single texture and use a custom key
{
	bool ok = false;

	Texture* newTexture = new Texture(filepath);
	if (newTexture->isBad())
	{
		delete newTexture;
	}
	else
	{
		std::pair<string, Texture*> thePair= pair<string, Texture*>(customKey, newTexture);

		mTextureMap.insert(thePair);
		ok = true;
	}
	return ok;
}
int TextureManager::AddTextureMany(const string* filepaths, int count) //add multiple textures with a single function and use the filepath as the key
{
	bool ok;
	int sucessfulCount = 0;
	for (int i = 0; i < count; i++)
	{
		ok = AddTexture(filepaths[i]);
		if (ok)
			sucessfulCount++;
	}
	return sucessfulCount;
}

//search functions
Texture* TextureManager::FindTexture(const string &key) const
{
	return mTextureMap.find(key)->second;
}
bool TextureManager::TextureExists(const string &key) const
{
	return FindTexture(key) != nullptr;
}

