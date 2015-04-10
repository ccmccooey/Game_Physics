/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  Sprite2DManager.h
*
*	Description:
*		This class manages sprites.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _SPRITE2D_MANAGER_H
#define _SPRITE2D_MANAGER_H

class Texture;
class Sprite2D;

#include <map>
#include <string>

using namespace std;


class Sprite2DManager
{
private:
	map<string, Sprite2D*> mSpriteMap;	

public:
	//constructors
	Sprite2DManager();
	~Sprite2DManager();

	//adding and removing textures
	bool AddSprite(const string &filepath); //add a single texture and use the filepath as the key, returns if it is successful
	bool AddSprite(const string &filepath, const string &customKey); //add a single texture and use a custom key, returns if it is successful
	bool AddSprite(Texture* texture, const string &customKey); //add a single sprite and use a custom key, returns if it is successful
	bool AddSprite(const string &filepath, int sourceX, int sourceY, int sourceW, int sourceH, const string &customKey); //add a single sprite using source info and use a custom key, returns if it is successful
	bool AddSprite(Texture* texture, int sourceX, int sourceY, int sourceW, int sourceH, const string &customKey); //add a single sprite using source info loaded from a texture and use a custom key , returns if it is successful

	//search functions
	Sprite2D* FindSprite(const string &key) const;
	bool SpriteExists(const string &key) const;

private:
	void RemoveAllSprites();
};

#endif