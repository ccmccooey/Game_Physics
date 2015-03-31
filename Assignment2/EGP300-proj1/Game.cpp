#include "Game.h"
#include "MainApp.h"
#include "TextureManager.h"
#include "Texture.h"
#include "MaterialManager.h"
#include "ModelManager.h"
#include "DisplayObject3DManager.h"
#include "DisplayObject3D.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "CameraContainer.h"
#include "GroundForceGenerator.h"
#include "GroundContactGenerator.h"
#include "Material.h"
#include "DrawData.h"
#include "MassAggregate.h"
#include "ObjectSpawner.h"
#include "Model.h"
#include "Level.h"
#include "Player.h"

#include <string>

using namespace std;

//constructors
Game::Game()
{
	Initialize();
}
Game::~Game()
{
	CleanUp();
}


void Game::LatchCameraToPlayer(CameraContainer* camera)
{
	camera->Latch(mPlayer->GetMassAggregate()->GetGraphicsObjectAt(0));
}

//initialization
void Game::Initialize()
{
	mMassAggregates = std::vector<MassAggregate*>();

	InitializeAssets();
	InitializeGround();
	InitializeMassAggregates();
}
void Game::InitializeAssets()
{
	string texPath = "Content/MassAggregateTextures/";

	//create the textures
	TextureManager* mTextureManager = MainApp::GetTextureManager();
	mTextureManager->AddTexture("Content/OtherTextures/Grass.png", "Grass");
	mTextureManager->AddTexture(texPath + "ParticleMetal.png", "ParticleMetal");
	mTextureManager->AddTexture(texPath + "SteelRod.png", "SteelRod");
	mTextureManager->AddTexture(texPath + "BungeeLeather.png", "BungeeLeather");
	mTextureManager->AddTexture(texPath + "GreenBlob.png", "GreenBlob");

	//create the materials
	MaterialManager* mMaterialManager = MainApp::GetMaterialManager();
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("Grass"), "Grass");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("ParticleMetal"), "ParticleMetal");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("SteelRod"), "SteelRod");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("BungeeLeather"), "BungeeLeather");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("GreenBlob"), "GreenBlob");

	//create the models
	ModelManager* pModelManager = MainApp::GetModelManager();
	Model* pGrass = new Model(mMaterialManager->FindMaterial("Grass"), Geometry::QUAD);
	pModelManager->AddModel(pGrass, "Grass");

}
void Game::InitializeGround()
{
	//create the ground
	DisplayObject3D *grass = new DisplayObject3D(MainApp::GetModelManager()->FindModel("Grass"));
	Transform *pGrassTransform = grass->getTransform();
	float groundHeight = -10.0f;

	pGrassTransform->SetPosition(-50.0f, groundHeight - 0.5f, 50.0f);
	pGrassTransform->SetScale(100.0f, 100.0f, 1.0f);
	pGrassTransform->SetRotationDegrees(90.0f, 0.0f, 0.0f);
	MainApp::GetGraphicsSystem()->AddObject(grass);

	GroundContactGenerator* groundContact = new GroundContactGenerator(groundHeight);
	MainApp::GetPhysicsSystem()->AddContactGenerator(groundContact);

	GroundForceGenerator* groundForce = new GroundForceGenerator(1.0f);
	MainApp::GetPhysicsSystem()->AddForceGenerator(groundForce);
}
void Game::InitializeMassAggregates()
{
	MassAggregate* ma;
	
	mSpawner = new ObjectSpawner();

	//create the player
	ma = new MassAggregate(MassAggregateGeometry::MA_Solid_Line, 0.0f, 0.0f, 0.0f);
	mPlayer = new Player(ma, mSpawner);
	mMassAggregates.push_back(ma);

	//create the mass aggregates
	std::string path = "Content/levelData.txt";
	bool loadOk = Level::LoadLevel(path, mSpawner);

	//test 2
	/*
	ma = new MassAggregate(MassAggregateGeometry::MA_Solid_PyramidWithTop, 0.0f, 0.0f, 0.0f);
	//ma->AddToSystems(mpParticleSystemReference, mpGraphicsSystemReference);
	mMassAggregates.push_back(ma);
	*/
}

//update all the mass aggregate graphics
void Game::Update(double t)
{
	mPlayer->FixedUpdate(t, mMassAggregates);
}
void Game::UpdateGraphicsObjects()
{
	unsigned int size = mMassAggregates.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mMassAggregates[i]->LinkPositions();
	}
	mSpawner->LinkPosition();
}

//cleanup
void Game::CleanUp()
{
	this->RemoveMassAggregates();

}
void Game::RemoveMassAggregates()
{
	delete mSpawner;
	delete mPlayer;

	//removes all mass aggregates from memory
	unsigned int size = mMassAggregates.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//mMassAggregates[i]->DeleteFromSystems(mpParticleSystemReference, mpGraphicsSystemReference);
		delete mMassAggregates[i];
	}
	mMassAggregates.clear();
}

//reset the mass aggregates
void Game::Reset()
{
	RemoveMassAggregates();
	//InitializeMassAggregates();
}