#ifndef _GAME_H
#define _GAME_H

#include "Vector3f.h"
#include <vector>

class CameraContainer;
class TextureManager;
class MassAggregate;
class MaterialManager;
struct MassAggregateModels;
class Model;
class Player;
struct DrawData;

class Game
{
private:
	
private:
	TextureManager* mTextureManager;
	MaterialManager* mMaterialManager;
	std::vector<MassAggregate*> mMassAggregates;
	MassAggregateModels* mModels;
	Model* mGrassModel;
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
	void RemoveGround();
};

#endif