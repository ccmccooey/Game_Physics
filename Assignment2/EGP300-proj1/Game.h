#ifndef _GAME_H
#define _GAME_H

#include <vector>

class TextureManager;
class Material;
class ParticleSystem;
class MassAggregate;
struct DrawData;

class Game
{
private:
	enum MaterialEnum
	{
		Particle_Metal = 0,
		Steel_Rod,

		Total_Materials
	};
private:
	TextureManager* mTextureManager;
	std::vector<MassAggregate*> mMaterials;
	std::vector<MassAggregate*> mMassAggregates;
	ParticleSystem* mpParticleSystemReference;

public:
	Game(ParticleSystem* particleSystem);
	~Game();

	void Reset();

	void Draw(DrawData* data);

private:
	void Initialize();
	void CleanUp();

	void InitializeAssets();
	void InitializeMassAggregates();
	void RemoveMassAggregates();
};

#endif