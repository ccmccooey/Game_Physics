#ifndef _SKY_BOX_H
#define _SKY_BOX_H

class Transform;
class Material;
class Texture;
class Model;

#include <string>
#include "Vector3f.h"
#include "DrawData.h"

class Skybox
{
private:
	Texture* mTexture;
	Material* mMaterial;
	Model* mModel;
	Transform* mTransform;

public:
	Skybox(const std::string &texturePath);
	~Skybox();

	void SetPostion(const Vector3f &position);

	void Draw(DrawData* data);
};

#endif