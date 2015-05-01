#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <vector>
#include "GuiOperationEnum.h"
#include "Vector3f.h"

class Ground;
struct ObjectMaterial;
class GameObject;
class DisplayPointer;

class Game
{
private:
	std::vector<GameObject*> mGameObjects;
	Ground* mGround;
	ObjectMaterial* mObjectMaterial;
	DisplayPointer* mDisplayPointer;
	unsigned int mDisplayPointerIndex;

public:
	Game();
	~Game();

	//accessors
	void GetDebugInfo(std::string &info) const;
	float GetObjectMass() const;
	float GetObjectSize() const;
	void GetObjectInfoString(std::string &info) const;

	//send gui events from the main app to the game
	void SendGuiEvent(GuiOperationEnum ev);

	//update function
	void Update(double t);

	//reset the simulation
	void Reset();

private:
	void CreateObjectSphere(const Vector3f &position);
	void CreateObjectBox(const Vector3f &position);
	void CreateObjectStaticBox(const Vector3f &position, const Vector3f &scale, const std::string &materialName);
	void CreateInitialScene();

	void Initialize();
	void CleanUp();
};

#endif