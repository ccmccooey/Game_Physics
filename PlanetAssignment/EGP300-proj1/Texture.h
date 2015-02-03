/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Texture.h
*
*	Description:
*		This class stores information about a texture in OpenGL. It is capable of loading textures from a file. It currently supports tga and bmp formats.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include "GLfiles.h"

class Texture
{
	//custom data enum for only textures
private:
	enum Image_Format
	{
		Targa = 0,
		Bitmap,
		Png,
		Unknown
	};

private:
	GLuint mTextureInt;
	std::string mName;
	int mWidth;
	int mHeight;
	bool mBad;

public:
	Texture();
	Texture(const std::string &filepath);
	~Texture();

	//accessors
	GLint GetTextureInt() const;
	std::string GetName() const;
	int getWidth() const;
	int getHeight() const;
	int getArea() const;
	bool isBad() const;

	//binding the texture for use
	void BindTexture();

public:
	bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
	bool LoadBMPTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
	bool LoadPNGTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);

private:
	Image_Format getFormat(const std::string &filepath);
};

#endif