#ifndef _MAIN_APP_H
#define _MAIN_APP_H

class Camera;
class GuiSystem;
class GraphicsSystem;
class Game;
class CameraContainer;
class Skybox;

class MainApp
{
private:
	static MainApp* msApplication;

private:
	GraphicsSystem* mGraphicsSystem;
	Game* mGame;
	Camera* mCamera;
	CameraContainer* mCameraContainer;
	GuiSystem*	mGuiSystem;	
	Skybox* mSkybox;

	int mWindowWidth;
	int mWindowHeight;
	bool mPaused;
	double mRunSpeed;
	float mCameraRotationSpeed;
	float mCameraMoveSpeed;
	bool mDebugInfo;
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
};

#endif