#ifndef _SKY_BOX_H
#define _SKY_BOX_H

class DisplayObject3D;
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
	DisplayObject3D* mObject;

public:
	Skybox(const std::string &texturePath);
	~Skybox();

	void SetPostion(const Vector3f &position);

	void Draw(DrawData* data);
};

#endif