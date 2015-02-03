/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Texture.cpp
*
*	Description:
*		This class stores information about a texture in OpenGL. It is capable of loading textures from a file. It currently supports tga and bmp formats.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Texture.h"
#include "lodepng.h"
#include <vector>

using namespace std;

Texture::Texture()
{
	mName = "NoName";
	mWidth = -1;
	mHeight = -1;
	mTextureInt = -1;
	mBad = true;
}
Texture::Texture(const std::string &filepath)
{
	mName = filepath;
	mWidth = -1;
	mHeight = -1;
	mBad = true;
	glGenTextures(1, &mTextureInt);
	glBindTexture(GL_TEXTURE_2D, mTextureInt);
	bool loadOK = false;

	Image_Format format = this->getFormat(filepath);
	
	if (format == Image_Format::Targa)
		loadOK = Texture::LoadTGATexture(filepath.c_str(),  GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	else if (format == Image_Format::Bitmap)
		loadOK = Texture::LoadBMPTexture(filepath.c_str(),  GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	else if (format == Image_Format::Png)
		loadOK = Texture::LoadPNGTexture(filepath.c_str(),  GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	mBad = !loadOK;
}

Texture::~Texture()
{

}

//binding the texture
void Texture::BindTexture()
{
	if (mTextureInt != -1)
	glBindTexture(GL_TEXTURE_2D, mTextureInt);
}

//accessors
GLint Texture::GetTextureInt() const
{
	return mTextureInt;
}
string Texture::GetName() const
{
	return mName;
}
int Texture::getWidth() const
{
	return mWidth;
}
int Texture::getHeight() const
{
	return mHeight;
}
int Texture::getArea() const
{
	return (mWidth * mHeight);
}
bool Texture::isBad() const
{
	return mBad;
}

//loading textures
bool Texture::LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
		return NULL;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	//TODO: Add mipmap stuff
	glGenerateMipmap(0);

	mWidth = nWidth;
	mHeight = nHeight;

	return true;
}
bool Texture::LoadBMPTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;

	pBits = gltReadBMPBits(szFileName, &nWidth, &nHeight);
	if (pBits == NULL)
		return NULL;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	//TODO: Add mipmap stuff
	glGenerateMipmap(0);

	mWidth = nWidth;
	mHeight = nHeight;

	return true;
}
bool Texture::LoadPNGTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	unsigned char* fileBitsBuffer = NULL;
	size_t fileSizeInBits = NULL;
	
	vector<unsigned char> png;
	vector<unsigned char> image;

	unsigned int errorCode, w, h;
	lodepng::State state;
	lodepng::load_file(png, szFileName);
	errorCode = lodepng::decode(image, w, h, state, png);

	if (errorCode == 0)
	{
		fileBitsBuffer = image.data();
	
		mWidth = (int)w;
		mHeight = (int)h;

	
		int nComponents;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, fileBitsBuffer);

	}

	return (errorCode == 0);
}

Texture::Image_Format Texture::getFormat(const string &filepath)
{
	unsigned int back = filepath.length() - 1;
	string extention = "";

	for (unsigned int i = back; i >= 0; i--)
	{
		extention = filepath[i] + extention;
		if (filepath[i] == '.')
		{
			break;
		}
	}

	Image_Format format = Image_Format::Unknown;
	if (extention == ".tga")
	{
		format = Image_Format::Targa;
	}
	else if (extention == ".bmp")
	{
		format = Image_Format::Bitmap;
	}
	else if (extention == ".png")
	{
		format = Image_Format::Png;
	}

	return format;
}


