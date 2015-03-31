#ifndef _GAME_H
#define _GAME_H

#include "Vector3f.h"
#include <vector>

class CameraContainer;
class MassAggregate;
class ObjectSpawner;
class Player;

class Game
{
private:
	
private:
	
	std::vector<MassAggregate*> mMassAggregates;
	ObjectSpawner* mSpawner;
	Player* mPlayer;

public:
	Game();
	//Game(ParticleSystem* particleSystem, DisplayObject3DManager* graphicsSystem);
	~Game();


	void UpdateGraphicsObjects();
	void Update(double t);
	void Reset();

	void LatchCameraToPlayer(CameraContainer* camera);

private:
	void Initialize();
	void CleanUp();

	void InitializeAssets();
	void InitializeGround();
	void InitializeMassAggregates();
	void RemoveMassAggregates();
};

#endif