/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  Sprite2DManager.cpp
*
*	Description:
*		This class manages sprites.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Sprite2DManager.h"
#include "Sprite2D.h"

//constructors
Sprite2DManager::Sprite2DManager()
{
	mSpriteMap = map<string, Sprite2D*>();
}
Sprite2DManager::~Sprite2DManager()
{
	RemoveAllSprites();
}

//removing the textures
void Sprite2DManager::RemoveAllSprites()
{
	map<string, Sprite2D*>::iterator iter = mSpriteMap.begin();
	map<string, Sprite2D*>::iterator back = mSpriteMap.end();

	while (iter != back)
	{
		Sprite2D* sprite = iter->second;
		delete sprite;
		iter->second = nullptr;
		iter++;
	}

	mSpriteMap.clear();
}

//adding new textures
bool Sprite2DManager::AddSprite(const string &filepath) //add a single texture and use the filepath as the key
{
	return AddSprite(filepath, filepath);
}
bool Sprite2DManager::AddSprite(const string &filepath, const string &customKey) //add a single texture and use a custom key
{
	bool ok = false;

	Sprite2D* newSprite = new Sprite2D(filepath);
	
	std::pair<string, Sprite2D*> thePair= pair<string, Sprite2D*>(customKey, newSprite);

	mSpriteMap.insert(thePair);
	ok = true;
	
	return ok;
}
bool Sprite2DManager::AddSprite(Texture* texture, const string &customKey) //add a single sprite and use a custom key, returns if it is successful
{
	return this->AddSprite(texture, 0, 0, texture->getWidth(), texture->getHeight(), customKey);
}
bool Sprite2DManager::AddSprite(const string &filepath, int sourceX, int sourceY, int sourceW, int sourceH, const string &customKey)
{
	bool ok = false;
	Sprite2D* newSprite = new Sprite2D(filepath, sourceX, sourceY, sourceW, sourceH);	
	std::pair<string, Sprite2D*> thePair= pair<string, Sprite2D*>(customKey, newSprite);
	mSpriteMap.insert(thePair);
	ok = true;
	
	return ok;
}
bool Sprite2DManager::AddSprite(Texture* texture, int sourceX, int sourceY, int sourceW, int sourceH, const string &customKey)
{
	bool ok = false;
	Sprite2D* newSprite = new Sprite2D(texture, sourceX, sourceY, sourceW, sourceH);	
	std::pair<string, Sprite2D*> thePair= pair<string, Sprite2D*>(customKey, newSprite);
	mSpriteMap.insert(thePair);
	ok = true;
	
	return ok;
}

//search functions
Sprite2D* Sprite2DManager::FindSprite(const string &key) const
{
	return mSpriteMap.find(key)->second;
}
bool Sprite2DManager::SpriteExists(const string &key) const
{
	return FindSprite(key) != nullptr;
}

