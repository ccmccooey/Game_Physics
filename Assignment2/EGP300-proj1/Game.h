#ifndef _GAME_H
#define _GAME_H

#include <vector>

class TextureManager;
class MassAggregate;
class MaterialManager;
class ParticleSystem;
class DisplayObject3DManager;
struct MassAggregateModels;
class Model;
struct DrawData;

class Game
{
private:
	
private:
	TextureManager* mTextureManager;
	MaterialManager* mMaterialManager;
	std::vector<MassAggregate*> mMassAggregates;
	ParticleSystem* mpParticleSystemReference;
	DisplayObject3DManager* mpGraphicsSystemReference;
	MassAggregateModels* mModels;
	Model* mGrassModel;

public:
	Game(ParticleSystem* particleSystem, DisplayObject3DManager* graphicsSystem);
	~Game();


	void UpdateGraphicsObjects();
	void Reset();

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