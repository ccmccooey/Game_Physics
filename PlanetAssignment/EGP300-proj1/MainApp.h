#ifndef _MAIN_APP_H
#define _MAIN_APP_H

class Camera;
class GuiSystem;
class PlanetManager;
class ParticleSystem;
class TextRenderer;
class Skybox;
struct DrawData;

#include "GLfiles.h"

class MainApp
{
private:
	Camera* mCamera;
	GuiSystem*	mGuiSystem;
	ParticleSystem* mParticleSystem;
	GLFrustum mViewFrustum3D;
	DrawData* mDrawData;
	GLShaderManager mShaderManager;
	TextRenderer*	mTextRenderer;
	PlanetManager* mPlanetManager;
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

	void CheckKeyboardInput(unsigned char key);
	void CheckSpecialKeyboardInput(int key, int x, int y);
	void CheckMouseInput(int x, int y, bool mouseDown, bool mouseClicked);
	void UpdateWindowSize(int w, int h);
	void FixedUpdate(double value);
	void IncreaseRunSpeed(double amount);
	void DecreaseRunSpeed(double amount);
	void CheckGui();
	void UpdateSkyboxPosition();

	void RenderScene();

private:
	void Initialize();
	void CleanUp();
};

#endif