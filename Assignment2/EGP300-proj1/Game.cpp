#include "Game.h"
#include "TextureManager.h"
#include "Texture.h"
#include "MaterialManager.h"
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
#include "MainApp.h"
#include "Model.h"
#include "Player.h"

#include <string>

using namespace std;

//constructors
Game::Game()
{
	Initialize();
}
/*
Game::Game(ParticleSystem* particleSystem, DisplayObject3DManager* graphicsSystem)
{
	mpParticleSystemReference = particleSystem;
	mpGraphicsSystemReference = graphicsSystem;
	Initialize();
}*/
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
	mTextureManager = new TextureManager();
	mTextureManager->AddTexture("Content/OtherTextures/Grass.png", "Grass");
	mTextureManager->AddTexture(texPath + "ParticleMetal.png", "ParticleMetal");
	mTextureManager->AddTexture(texPath + "SteelRod.png", "SteelRod");
	mTextureManager->AddTexture(texPath + "BungeeLeather.png", "BungeeLeather");
	mTextureManager->AddTexture(texPath + "GreenBlob.png", "GreenBlob");

	//create the materials
	mMaterialManager = new MaterialManager();
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("Grass"), "Grass");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("ParticleMetal"), "ParticleMetal");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("SteelRod"), "SteelRod");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("BungeeLeather"), "BungeeLeather");
	mMaterialManager->AddMaterial(mTextureManager->FindTexture("GreenBlob"), "GreenBlob");

	//create the models
	Model* pModelPoint = new Model(mMaterialManager->FindMaterial("ParticleMetal"), Geometry::CUBE);
	Model* pModelLine = new Model(mMaterialManager->FindMaterial("SteelRod"), Geometry::CUBE);
	mModels = new MassAggregateModels(pModelPoint, pModelLine, pModelLine, pModelPoint, pModelPoint);

	mGrassModel = new Model(mMaterialManager->FindMaterial("Grass"), Geometry::QUAD);
}
void Game::InitializeGround()
{
	//create the ground
	DisplayObject3D *grass = new DisplayObject3D(mGrassModel);
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
	

	//test 1
	/*
	MassAggregate* ma = new MassAggregate(mModels, MassAggregateGeometry::MA_Point, 0.0f, 0.0f, 0.0f);
	ma->AddToSystems(mpParticleSystemReference, mpGraphicsSystemReference);
	mMassAggregates.push_back(ma);

	Particle* p = ma->GetParticleAt(0);
	if (p != nullptr)
		p->AddVelocity(Vector3f::unitX * 2.0f);*/

	ma = new MassAggregate(mModels, MassAggregateGeometry::MA_Solid_Line, 0.0f, 0.0f, 0.0f);
	mPlayer = new Player(ma);
	mMassAggregates.push_back(ma);

	//test 2
	ma = new MassAggregate(mModels, MassAggregateGeometry::MA_Solid_PyramidWithTop, 0.0f, 0.0f, 0.0f);
	//ma->AddToSystems(mpParticleSystemReference, mpGraphicsSystemReference);
	mMassAggregates.push_back(ma);

	//initial velocities
	/*
	Particle* p;
	p = ma->GetParticleAt(0);
	if (p != nullptr)
		p->AddVelocity(Vector3f::unitX * 1.5f + Vector3f::unitZ * 1.0f);
	p = ma->GetParticleAt(1);
	if (p != nullptr)
		p->AddVelocity(Vector3f::unitX * -1.5f + Vector3f::unitZ * 1.0f);*/
}

//update all the mass aggregate graphics
void Game::Update(double t)
{
	mPlayer->FixedUpdate(t);
}
void Game::UpdateGraphicsObjects()
{
	unsigned int size = mMassAggregates.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mMassAggregates[i]->LinkPositions();
	}
}

//cleanup
void Game::CleanUp()
{
	this->RemoveMassAggregates();
	this->RemoveGround();

	delete mPlayer;
	delete mModels;	

	delete mMaterialManager;
	delete mTextureManager;
}
void Game::RemoveMassAggregates()
{
	//removes all mass aggregates from memory
	unsigned int size = mMassAggregates.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//mMassAggregates[i]->DeleteFromSystems(mpParticleSystemReference, mpGraphicsSystemReference);
		delete mMassAggregates[i];
	}
	mMassAggregates.clear();
}
void Game::RemoveGround()
{
	delete mGrassModel;
}

//reset the mass aggregates
void Game::Reset()
{
	RemoveMassAggregates();
	//InitializeMassAggregates();
}