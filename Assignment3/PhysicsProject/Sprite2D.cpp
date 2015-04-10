#include "Sprite2D.h"
#include "Vector3f.h"
#include "Texture.h"
#include "MeshCreator.h"
#include "BasicGeometry.h"

Sprite2D::Sprite2D(const std::string &filepath)
{
	this->InitializeTexture(filepath);
	this->InitializeBatch();
	mManagesTexture = true;
}
Sprite2D::Sprite2D(const std::string &filepath, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	this->InitializeTexture(filepath);
	this->InitializeBatch(sourceX, sourceY, sourceWidth, sourceHeight);
	mManagesTexture = true;
}
Sprite2D::Sprite2D(Texture* texture, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	mTexture = texture;
	this->InitializeBatch(sourceX, sourceY, sourceWidth, sourceHeight);
	mManagesTexture = false;
}
Sprite2D::Sprite2D(Texture* texture)
{
	mTexture = texture;
	this->InitializeBatch();
	mManagesTexture = false;
}
Sprite2D::~Sprite2D()
{
	delete mBatch;
	if (mManagesTexture)
	{
		delete mTexture;
	}
}

//accessors
int Sprite2D::getWidth() const
{
	return mWidth;
}
int Sprite2D::getHeight() const
{
	return mHeight;
}
int Sprite2D::getArea() const
{
	return mWidth * mHeight;
}
Texture* Sprite2D::getTexture() const
{
	return mTexture;
}

//creating the quad batch for openGL to draw on
void Sprite2D::InitializeBatch()
{
	mBatch = new GLBatch();
	mWidth = mTexture->getWidth();
	mHeight = mTexture->getHeight();

	BasicGeometry::setDataToQuad(mBatch);
}
void Sprite2D::InitializeBatch(int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	mBatch = new GLBatch();

	mWidth = sourceWidth;
	mHeight = sourceHeight;

	float textureWidth = (float)mTexture->getWidth();
	float textureHeight = (float)mTexture->getHeight();

	float uvX, uvY, uvW, uvH;
	uvX = (float)sourceX / textureWidth;
	uvY = (float)sourceY / textureHeight;
	uvW = (float)sourceWidth / textureWidth;
	uvH = (float)sourceHeight / textureHeight;

	BasicGeometry::setDataToQuad(mBatch, uvX, uvY, uvW, uvH);
}

//creating the texture from a file path for openGL to bind
void Sprite2D::InitializeTexture(const std::string &filepath)
{
	mTexture = new Texture(filepath);
}

//draw the sprite
void Sprite2D::Draw(GLShaderManager* shaderManager, M3DMatrix44f &mat)
{
	mTexture->BindTexture();

	shaderManager->UseStockShader(GLT_SHADER_TEXTURE_REPLACE, mat, 0);

	mBatch->Draw();
}