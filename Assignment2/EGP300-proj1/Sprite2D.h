#ifndef _SPRITE2D_H
#define _SPRITE2D_H

#include "GLfiles.h"
#include "Texture.h"
class Texture;

class Sprite2D
{
private:
	GLBatch* mBatch;
	Texture* mTexture;
	int mWidth;
	int mHeight;
	bool mManagesTexture;

public:
	Sprite2D(const std::string &filepath);
	Sprite2D(const std::string &filepath, int sourceX, int sourceY, int sourceWidth, int sourceHeight);
	Sprite2D(Texture* texture, int sourceX, int sourceY, int sourceWidth, int sourceHeight);
	Sprite2D(Texture* texture);
	~Sprite2D();

	//accessors
	int getWidth() const;
	int getHeight() const;
	int getArea() const;
	Texture* getTexture() const;

	void Draw(GLShaderManager* shaderManager, M3DMatrix44f &mat);

private:
	void InitializeBatch();
	void InitializeBatch(int sourceX, int sourceY, int sourceWidth, int sourceHeight);
	void InitializeTexture(const std::string &filepath);

	
};

#endif