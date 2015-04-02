#include "GraphicsSystem.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include "ModelManager.h"
#include "DisplayObject3DManager.h"
#include "TextRenderer.h"
#include "DrawData.h"
#include "Camera.h"
#include "GLfiles.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_PERSPECTIVE_NEAR 1.0f
#define DEFAULT_PERSPECTIVE_FAR 1000.0f

//singleton
GraphicsSystem* GraphicsSystem::msSystem = nullptr;

//constructors
GraphicsSystem::GraphicsSystem()
{
	Initialize();
}
GraphicsSystem::~GraphicsSystem()
{
	CleanUp();
}
void GraphicsSystem::CreateSystem()
{
	if (msSystem == nullptr)
	{
		msSystem = new GraphicsSystem();
	}
}
void GraphicsSystem::DestroySystem()
{
	if (msSystem != nullptr)
	{
		delete msSystem;
		msSystem = nullptr;
	}
}

//initialization and cleanup
void GraphicsSystem::Initialize()
{
	//create the asset managers
	mTextureManager = new TextureManager();
	mShaderManager = new ShaderManager();
	mMaterialManager = new MaterialManager();
	mModelManager = new ModelManager();

	//stock shaders for basic 3D rendering
	mStockShaders = new GLShaderManager();
	mStockShaders->InitializeStockShaders();

	//create the renderer for displaying text
	mTextRenderer = new TextRenderer();

	//perspective matrix
	mViewFrustum3D = new GLFrustum();
	mNear = DEFAULT_PERSPECTIVE_NEAR;
	mFar = DEFAULT_PERSPECTIVE_FAR;
	UpdateWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	//draw data
	mDrawData = new DrawData();
	mDrawData->textRenderer = mTextRenderer;
	mDrawData->stockShaders = mStockShaders;
	mDrawData->shaderManager = mShaderManager;
}
void GraphicsSystem::LoadContent()
{

}
void GraphicsSystem::CleanDisplayList()
{
	mDisplayList->RemoveAllObjects();
}
void GraphicsSystem::CleanUp()
{
	delete mDisplayList;
	mDisplayList = nullptr;

	delete mModelManager;
	mModelManager = nullptr;

	delete mMaterialManager;
	mMaterialManager = nullptr;

	delete mShaderManager;
	mShaderManager = nullptr;

	delete mTextureManager;
	mTextureManager = nullptr;
}

//static accessors
GraphicsSystem* GraphicsSystem::Instance()
{
	return msSystem;
}
Texture* GraphicsSystem::GetTexture(const std::string &key)
{
	return msSystem->mTextureManager->FindTexture(key);
}
Material* GraphicsSystem::GetMaterial(const std::string &key)
{
	return msSystem->mMaterialManager->FindMaterial(key);
}
Model* GraphicsSystem::GetModel(const std::string &model)
{
	return msSystem->mModelManager->FindModel(model);
}
DisplayObject3DManager* GraphicsSystem::GetDisplayObjectManager()
{
	return msSystem->mDisplayList;
}

//adding and removing graphics objects
void GraphicsSystem::AddDisplayObject(DisplayObject3D* object)
{
	msSystem->AddDisplayObject(object);
}
void GraphicsSystem::RemoveDisplayObject(DisplayObject3D* object)
{
	msSystem->RemoveDisplayObject(object);
}

//change the perspective of the view frustum
void GraphicsSystem::ChangePersective(float nearView, float farView)
{
	mNear = 1.0f;
	mFar = farView;
	UpdateWindowSize(mWindowWidth, mWindowHeight);
}

//update the window width and height when it is resized
void GraphicsSystem::UpdateWindowSize(int w, int h)
{
	glViewport(0, 0, w, h);

	mWindowWidth = w;
	mWindowHeight = h;

	mViewFrustum3D->SetPerspective(35.0f, (float)(mWindowWidth / mWindowHeight), mNear, mFar);
}

//draw call
void GraphicsSystem::RenderScene(DrawData *data, Camera* camera)
{
	msSystem->Draw(data, camera);
}
void GraphicsSystem::Draw(DrawData *data, Camera* camera) const
{
	M3DMatrix44f &view = camera->getView();
	const M3DMatrix44f &projection = mViewFrustum3D->GetProjectionMatrix();

	mDrawData->frustum = &mViewFrustum3D->GetProjectionMatrix();
	mDrawData->view = &view;

	mDisplayList->Draw(mDrawData);
}