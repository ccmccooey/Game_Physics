#include "Skybox.h"
#include "Texture.h"
#include "Material.h"
#include "DisplayObject3D.h"
#include "Model.h"

Skybox::Skybox(const std::string &texturePath)
{
	mTexture = new Texture(texturePath);
	mMaterial = new Material(mTexture);
	mModel = new Model(mMaterial, Geometry::CUBE);
	mObject = new DisplayObject3D(mModel);
	mObject->getTransform()->SetPosition(Vector3f::zero);
	mObject->getTransform()->Scale(1000.0f);
}
Skybox::~Skybox()
{
	delete mObject;
	delete mModel;
	delete mMaterial;
	delete mTexture;
}

void Skybox::Draw(DrawData* data)
{
	mObject->Draw(data);
}

void Skybox::SetPostion(const Vector3f &position)
{
	mObject->getTransform()->SetPosition(position);
}