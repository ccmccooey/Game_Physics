#include "Game.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Material.h"
#include "DrawData.h"
#include "MassAggregate.h"

#include <string>

using namespace std;

//constructors
Game::Game(ParticleSystem* particleSystem)
{
	mpParticleSystemReference = particleSystem;
	Initialize();
}
Game::~Game()
{
	CleanUp();
}

//initialization
void Game::Initialize()
{
	mMassAggregates = std::vector<MassAggregate*>();

	InitializeAssets();
	InitializeMassAggregates();
}
void Game::InitializeAssets()
{
	string texPath = "Content/MassAggregateTextures/";

	mTextureManager = new TextureManager();
	mTextureManager->AddTexture(texPath + "ParticleMetal.png", "ParticleMetal");
	mTextureManager->AddTexture(texPath + "SteelRod.png", "SteelRod");
	mTextureManager->AddTexture(texPath + "BungeeLeather.png", "BungeeLeather");
	mTextureManager->AddTexture(texPath + "GreenBlob.png", "GreenBlob");
}
void Game::InitializeMassAggregates()
{

}

//cleanup
void Game::CleanUp()
{
	this->RemoveMassAggregates();

	delete mTextureManager;
}
void Game::RemoveMassAggregates()
{

}

//reset the mass aggregates
void Game::Reset()
{
	RemoveMassAggregates();
	InitializeMassAggregates();
}

//draw
void Game::Draw(DrawData* data)
{
	unsigned int size = mMassAggregates.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mMassAggregates[i]->Draw(data);
	}
}