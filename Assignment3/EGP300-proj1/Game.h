#ifndef _GAME_H
#define _GAME_H

#include "Vector3f.h"
#include <vector>
#include <string>

class CameraContainer;
class MassAggregate;
class ObjectSpawner;
class Player;
class Enemy;

class Game
{
private:
	
private:
	bool mMACreated;
	std::vector<MassAggregate*> mMassAggregates;
	ObjectSpawner* mSpawner;
	Player* mPlayer;
	Enemy* mEnemy;
	CameraContainer* mpCamera;

public:
	Game();
	//Game(ParticleSystem* particleSystem, DisplayObject3DManager* graphicsSystem);
	~Game();


	void UpdateGraphicsObjects();
	void Update(double t);
	void Reset();

	void LatchCameraToPlayer(CameraContainer* camera);
	void GetDebugInfo(std::string &info) const;

private:
	void Initialize();
	void CleanUp();

	void InitializeAssets();
	void InitializeGround();
	void InitializeMassAggregates();
	void RemoveMassAggregates();
};

#endif