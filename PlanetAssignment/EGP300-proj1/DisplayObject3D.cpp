/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  DisplayObject3D.cpp
*
*	Description:
*		This class represents a 3D display object.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "DisplayObject3D.h"
#include "Model.h"
#include "Transform.h"
#include "GLfiles.h"

//display object class just stores transform data and a pointer to a model/mesh
DisplayObject3D::DisplayObject3D(Model* model)
{
	mModel = model;
	mTransform = new Transform();
	mMaterial = nullptr;
}
DisplayObject3D::DisplayObject3D(const DisplayObject3D &rhs)
{
	mModel = rhs.mModel;
	mTransform = new Transform(*rhs.mTransform);
	mMaterial = rhs.mMaterial;
}

DisplayObject3D::~DisplayObject3D()
{
	delete mTransform;
}

Transform* DisplayObject3D::getTransform()
{
	return mTransform;
}

void DisplayObject3D::SetMaterial(Material* material)
{
	mMaterial = material;
}
void DisplayObject3D::RemoveMaterial()
{
	mMaterial = nullptr;
}

//draw
void DisplayObject3D::Draw(GLShaderManager &shaderManager, const M3DMatrix44f &frustum, M3DMatrix44f &view)
{
	if (mModel == nullptr)
	{
		throw;
		return;
	}

	M3DMatrix44f modelView;
	M3DMatrix44f mvpMatrix;

	

	m3dMatrixMultiply44(modelView, view, mTransform->GetModelMatrix());
	m3dMatrixMultiply44(mvpMatrix, frustum, modelView);
	//shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);

	
	if (mMaterial == nullptr)
		mModel->Draw(&shaderManager, frustum, modelView, mvpMatrix);
	else
		mModel->Draw(&shaderManager, frustum, modelView, mvpMatrix, mMaterial);
	//mModel->Draw(&shaderManager, mvpMatrix);
}