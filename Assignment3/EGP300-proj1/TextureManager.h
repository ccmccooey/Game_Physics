/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  TextureManager3D.h
*
*	Description:
*		This class manages textures.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _TEXTURE_MANAGER_3D_H
#define _TEXTURE_MANAGER_3D_H

class Texture;

#include <string>
#include <map>

using namespace std;

class TextureManager
{
private:
	map<string, Texture*> mTextureMap;	

public:
	//constructors
	TextureManager();
	~TextureManager();

	//adding and removing textures
	bool AddTexture(const string &filepath); //add a single texture and use the filepath as the key, returns if it is successful
	bool AddTexture(const string &filepath, const string &customKey); //add a single texture and use a custom key, returns if it is successful
	int AddTextureMany(const string* filepaths, int count); //add multiple textures with a single function and use the filepath as the key, returns the number of textures that were successful loaded


	//search functions
	Texture* FindTexture(const string &key) const;
	bool TextureExists(const string &key) const;

private:
	void RemoveAllTextures();

};


#endif

