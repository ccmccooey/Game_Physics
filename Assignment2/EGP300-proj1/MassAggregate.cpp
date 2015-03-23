#include "MassAggregate.h"
#include "ParticleRod.h"
#include "Particle.h"
#include "DisplayObject3D.h"
#include "ParticleSystem.h"
#include "GameObject.h"
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

	//remove the display
	size = mDisplayLines.size();
	for (i = 0; i < size; i++)
	{
		delete mDisplayLines[i];
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

//setters

//creating the geometry
void MassAggregate::CreateBody(MassAggregateModels* models)
{
	mAddedToSystems = false;
	mDisplayLines = vector<DisplayObject3D*>();

	mParticles = vector<GameObject*>();
	mLinks = vector<ParticleLink*>();

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

void MassAggregate::InsertParticle(Model* model, const Vector3f &position)
{
	GameObject* obj = new GameObject(model, mInitialPosition);
	mParticles.push_back(obj);
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
	//create the graphics particles
	

	/*
	//create the graphics rod
	objLink = new DisplayObject3D(models->modelRod);
	mDisplayLines.push_back(objLink);

	particle = new Particle(mDisplayPoints[0]->getTransform());
	particle->SetPosition(mInitialPosition);
	mParticles.push_back(particle);

	particle = new Particle(mDisplayPoints[1]->getTransform());
	particle->SetPosition(mInitialPosition + Vector3f::unitX);
	mParticles.push_back(particle);

	rod = new ParticleRod();
	rod->mParticleA = mParticles[0];
	rod->mParticleB = mParticles[1];
	mLinks.push_back((ParticleLink*)rod);*/

}
#pragma endregion
#pragma region Create Cube
void MassAggregate::CreateBodyCube(MassAggregateModels* models)
{

}
#pragma endregion
#pragma region Create Tetrahedron
void MassAggregate::CreateBodyTetrahedron(MassAggregateModels* models)
{

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
			physicsSystem->AddContactGenerator(mLinks[i]);
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
			physicsSystem->RemoveContactGenerator(mLinks[i]);		
		}
		mAddedToSystems = false;
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