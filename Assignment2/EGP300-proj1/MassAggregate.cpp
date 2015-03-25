#include "MassAggregate.h"
#include "ParticleRod.h"
#include "Particle.h"
#include "DisplayObject3D.h"
#include "DisplayObject3DManager.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "GameObjectLink.h"
#include "DebugLogger.h"

using namespace std;

//constructors
MassAggregate::MassAggregate(MassAggregateModels* models)
{
	mGeometryType = MA_DEFAULT_GEOMETRY;
	mInitialPosition = MA_DEFAULT_POSITION;
	CreateBody(models);
}
MassAggregate::MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry)
{
	mGeometryType = geometry;
	mInitialPosition = MA_DEFAULT_POSITION;
	CreateBody(models);
}
MassAggregate::MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, const Vector3f &position)
{
	mGeometryType = geometry;
	mInitialPosition = position;
	CreateBody(models);
}
MassAggregate::MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, float initialX, float initialY, float initialZ)
{
	mGeometryType = geometry;
	mInitialPosition = Vector3f(initialX, initialY, initialZ);
	CreateBody(models);
}
MassAggregate::MassAggregate(MassAggregateModels* models, const MassAggregate &rhs)
{
	mGeometryType = rhs.mGeometryType;
	mInitialPosition = rhs.mInitialPosition;
	CreateBody(models);
}
MassAggregate::~MassAggregate()
{
	unsigned int i;
	unsigned int size;

	if (mAddedToSystems)
	{
		DebugLogger::WriteError("A mass aggregate did not get removed from the systems before getting deleted from memory");
	}

	//remove the physics
	size = mParticles.size();
	for (i = 0; i < size; i++)
	{
		delete mParticles[i];
	}
	size = mLinks.size();
	for (i = 0; i < size; i++)
	{
		delete mLinks[i];
	}
}

//accessors
Particle* MassAggregate::GetParticleAt(unsigned int index) const
{
	if (index >= 0 && index < mParticles.size())
	{
		return mParticles[index]->GetPhysicsObject();
	}
	return nullptr;
}
//setters

//creating the geometry
void MassAggregate::CreateBody(MassAggregateModels* models)
{
	mAddedToSystems = false;

	mParticles = vector<GameObject*>();
	mLinks = vector<GameObjectLink*>();

	switch(mGeometryType)
	{
	case MassAggregateGeometry::MA_Point:
		CreateBodyPoint(models);
		break;
	case MassAggregateGeometry::MA_Solid_Line:
		CreateBodyLine(models);
		break;
	case MassAggregateGeometry::MA_Solid_Cube:
		CreateBodyCube(models);
		break;
	case MassAggregateGeometry::MA_Solid_Tetrahedron:
		CreateBodyTetrahedron(models);
		break;
	}
}

void MassAggregate::InsertParticle(Model* model, const Vector3f &relativePosition)
{
	GameObject* obj = new GameObject(model, mInitialPosition + relativePosition);
	mParticles.push_back(obj);
}
void MassAggregate::InsertLink(Model* model, int particleIndexA, int particleIndexB, LinkTypes type)
{
	if (type == LinkTypes::Rod)
	{
		ParticleRod* rod = new ParticleRod(8.0f);
		rod->mParticleA = mParticles[particleIndexA]->GetPhysicsObject();
		rod->mParticleB = mParticles[particleIndexB]->GetPhysicsObject();
		GameObjectLink* link = new GameObjectLink(model, rod);		
		mLinks.push_back(link);
	}
}

#pragma region Create Point
void MassAggregate::CreateBodyPoint(MassAggregateModels* models)
{
	InsertParticle(models->modelParticle, mInitialPosition);
}
#pragma endregion
#pragma region Create Line
void MassAggregate::CreateBodyLine(MassAggregateModels* models)
{
	InsertParticle(models->modelParticle, Vector3f::zero);
	InsertParticle(models->modelParticle, Vector3f::unitX * 10.0f +Vector3f::unitY * 5.0f);
	InsertLink(models->modelRod, 0, 1, LinkTypes::Rod);
}
#pragma endregion
#pragma region Create Cube
void MassAggregate::CreateBodyCube(MassAggregateModels* models)
{
	float d = 5.0f;

	//bottom square
	InsertParticle(models->modelParticle, Vector3f::zero);
	InsertParticle(models->modelParticle, Vector3f(d, 0.0f, 0.0f));
	InsertParticle(models->modelParticle, Vector3f(d, 0.0f, d));
	InsertParticle(models->modelParticle, Vector3f(0.0f, 0.0f, d));
	//top square
	InsertParticle(models->modelParticle, Vector3f::zero);
	InsertParticle(models->modelParticle, Vector3f(d, d, 0.0f));
	InsertParticle(models->modelParticle, Vector3f(d, d, d));
	InsertParticle(models->modelParticle, Vector3f(0.0f, d, d));

	InsertLink(models->modelRod, 0, 1, LinkTypes::Rod);
}
#pragma endregion
#pragma region Create Tetrahedron
void MassAggregate::CreateBodyTetrahedron(MassAggregateModels* models)
{
	InsertParticle(models->modelParticle, Vector3f::zero);
	InsertParticle(models->modelParticle, Vector3f::zero + Vector3f::unitX * 5.0f);
	InsertParticle(models->modelParticle, Vector3f::zero + Vector3f::unitZ * 5.0f);
	//InsertParticle(models->modelParticle, Vector3f::zero + Vector3f::unitZ);

	InsertLink(models->modelRod, 0, 1, LinkTypes::Rod);
	InsertLink(models->modelRod, 1, 2, LinkTypes::Rod);
	InsertLink(models->modelRod, 2, 0, LinkTypes::Rod);
	//InsertLink(models->modelRod, 1, 2, LinkTypes::Rod);
	//InsertLink(models->modelRod, 1, 3, LinkTypes::Rod);
	//InsertLink(models->modelRod, 2, 3, LinkTypes::Rod);
}
#pragma endregion

//adding to physics system
void MassAggregate::AddToSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem)
{
	if (!mAddedToSystems)
	{
		unsigned int i;
		unsigned int size;

		size = mParticles.size();
		for (i = 0; i < size; i++)
		{
			mParticles[i]->AddToSystems(physicsSystem, graphicsSystem);
		}
		size = mLinks.size();
		for (i = 0; i < size; i++)
		{
			physicsSystem->AddContactGenerator(mLinks[i]->GetLink());
			graphicsSystem->AddObject(mLinks[i]->GetGraphicsObject());
		}
		mAddedToSystems = true;
	}
}
void MassAggregate::DeleteFromSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem)
{
	if (mAddedToSystems)
	{
		unsigned int i;
		unsigned int size;

		size = mParticles.size();
		for (i = 0; i < size; i++)
		{
			mParticles[i]->DeleteFromSystems(physicsSystem, graphicsSystem);
		}
		size = mLinks.size();
		for (i = 0; i < size; i++)
		{
			physicsSystem->RemoveContactGenerator(mLinks[i]->GetLink());
			graphicsSystem->RemoveObject(mLinks[i]->GetGraphicsObject());
		}
		mAddedToSystems = false;
	}
}


void MassAggregate::LinkPositions() //link the position of the graphics object from the physics object
{
	unsigned int i;
	unsigned int size;

	size = mParticles.size();
	for (i = 0; i < size; i++)
	{
		mParticles[i]->LinkPositions();
	}
	size = mLinks.size();
	for (i = 0; i < size; i++)
	{
		mLinks[i]->LinkPositions();
	}
}

/*
//draw function
void MassAggregate::Draw(DrawData* drawData)
{
	unsigned int i;
	unsigned int size;

	size = mDisplayPoints.size();
	for (i = 0; i < size; i++)
	{
		mDisplayPoints[i]->Draw(drawData);
	}
	size = mDisplayLines.size();
	for (i = 0; i < size; i++)
	{
		mDisplayLines[i]->Draw(drawData);
	}
}*/