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
	mTransform = new Transform();
	mTransform->SetPosition(Vector3f::zero);
	mTransform->Scale(1000.0f);
}
Skybox::~Skybox()
{
	delete mTransform;
	delete mModel;
	delete mMaterial;
	delete mTexture;
}

void Skybox::Draw(DrawData* data)
{
	M3DMatrix44f modelView;
	M3DMatrix44f mvpMatrix;

	//m3dMatrixMultiply44(modelView, *data->view, mTransform->GetModelMatrix());
	//m3dMatrixMultiply44(mvpMatrix, *data->frustum, modelView);
	//shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
	m3dMatrixMultiply44(mvpMatrix, *data->frustum, mTransform->GetModelMatrix());

	mModel->Draw(data->shaderManager, *data->frustum, modelView, mvpMatrix);
}

void Skybox::SetPostion(const Vector3f &position)
{
	mTransform->SetPosition(position);
}