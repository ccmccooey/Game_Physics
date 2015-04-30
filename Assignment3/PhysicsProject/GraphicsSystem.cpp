#include <iostream>
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
	msSystem = this;

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
	bool ok = mStockShaders->InitializeStockShaders();
	if (!ok)
	{
		printf("Error Initializing stock shaders\n");
	}

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
	mDrawData->frustum = &mViewFrustum3D->GetProjectionMatrix();

	//create the display list
	mDisplayList = new DisplayObject3DManager();
}

//loading content
void GraphicsSystem::LoadContent()
{
	LoadTextureAndAddMaterial("Content/ObjectTextures/AirFilled.png", "AirFilled");	
	LoadTextureAndAddMaterial("Content/ObjectTextures/Wood.png", "Wood");
	LoadTextureAndAddMaterial("Content/ObjectTextures/Plastic.png", "Plastic");
	LoadTextureAndAddMaterial("Content/ObjectTextures/Steel.png", "Steel");
	LoadTextureAndAddMaterial("Content/ObjectTextures/Iron.png", "Iron");

	LoadTextureAndAddMaterial("Content/ObjectTextures/ContactDisplay.png", "ContactDisplay");
	LoadTextureAndAddMaterial("Content/ObjectTextures/DisplayPointer.png", "DisplayPointer");

	LoadTextureAndAddMaterial("Content/OtherTextures/Grass.png", "Grass");
	LoadTextureAndAddMaterial("Content/OtherTextures/Dirt.png", "Dirt");

	mMaterialManager->AddMaterial(mTextureManager->FindTexture("Dirt"), Color::White, ShaderType::SHADER_TEXTURE_TILE_REPLACE, "DirtTerrain");
}
void GraphicsSystem::LoadTextureAndAddMaterial(const std::string &texturePath, const std::string key) //create both a texture and material asset
{
	mTextureManager->AddTexture(texturePath, key);
	Texture* texture = mTextureManager->FindTexture(key);
	if (texture != nullptr)
	{
		mMaterialManager->AddMaterial(texture, key);
	}
	else
	{
		std::cerr << "ERROR: Could not find texture with key (" << key << ") using filepath (" << texturePath << ")" << std::endl;
	}
}

//clean up functions
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

//non-static accessors may be removed later
GLShaderManager* GraphicsSystem::GetStockShaders() const
{
	return mStockShaders;
}
TextRenderer* GraphicsSystem::GetTextRenderer() const
{
	return mTextRenderer;
}
DrawData* GraphicsSystem::GetDrawData() const
{
	return mDrawData;
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
ShaderBase* GraphicsSystem::GetShader(ShaderType type)
{
	return msSystem->mShaderManager->GetShaderPtr(type);
}
DisplayObject3DManager* GraphicsSystem::GetDisplayObjectManager()
{
	return msSystem->mDisplayList;
}

//adding and removing graphics objects
void GraphicsSystem::AddDisplayObject(DisplayObject3D* object)
{
	msSystem->mDisplayList->AddObject(object);
}
void GraphicsSystem::RemoveDisplayObject(DisplayObject3D* object)
{
	msSystem->mDisplayList->RemoveObject(object);
}
void GraphicsSystem::RemoveAllDisplayObjects()
{
	msSystem->mDisplayList->RemoveAllObjects();
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
void GraphicsSystem::RenderScene(Camera* camera)
{
	msSystem->Draw(camera);
}
void GraphicsSystem::Draw(Camera* camera) const
{
	M3DMatrix44f &view = camera->getView();
	const M3DMatrix44f &projection = mViewFrustum3D->GetProjectionMatrix();

	mDrawData->frustum = &mViewFrustum3D->GetProjectionMatrix();
	mDrawData->view = &view;

	mDisplayList->Draw(mDrawData);
}