#ifndef _MAIN_APP_H
#define _MAIN_APP_H

class Camera;
class GuiSystem;
class ParticleSystem;
class TextureManager;
class MaterialManager;
class ModelManager;
class DisplayObject3DManager;
class TextRenderer;
class Game;
class CameraContainer;
class Skybox;
struct DrawData;

#include "GLfiles.h"

class MainApp
{
private:
	static MainApp* msApplication;

private:
	Camera* mCamera;
	CameraContainer* mCameraContainer;
	GuiSystem*	mGuiSystem;
	ParticleSystem* mParticleSystem;
	GLFrustum mViewFrustum3D;
	DrawData* mDrawData;
	DisplayObject3DManager* mDisplayList;
	GLShaderManager mShaderManager;
	TextureManager* mTextureManager;
	MaterialManager* mMaterialManager;
	ModelManager* mModelManager;
	TextRenderer*	mTextRenderer;
	Game* mGame;
	Skybox* mSkybox;

	int mWindowWidth;
	int mWindowHeight;
	bool mPaused;
	double mRunSpeed;
	float mCameraRotationSpeed;
	float mCameraMoveSpeed;
	bool mUpdateOnlyOnce;

public:
	MainApp();
	~MainApp();

	void CheckMouseInput(int x, int y, bool mouseDown, bool mouseClicked);
	void CheckCameraMovement();
	void UpdateWindowSize(int w, int h);
	void FixedUpdate(double value);
	void IncreaseRunSpeed(double amount);
	void DecreaseRunSpeed(double amount);
	void CheckGui();
	void UpdateDebugInformation();
	void UpdateSkyboxPosition();

	void RenderScene();

private:
	void Initialize();
	void CleanUp();

public:
	static MainApp* GetApp();
	static ParticleSystem* GetPhysicsSystem();
	static DisplayObject3DManager* GetGraphicsSystem();
	static TextureManager* GetTextureManager();
	static MaterialManager* GetMaterialManager();
	static ModelManager* GetModelManager();
};

#endif