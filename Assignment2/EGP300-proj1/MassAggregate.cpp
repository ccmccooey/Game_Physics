#include "MassAggregate.h"
#include "ParticleRod.h"
#include "Particle.h"
#include "DisplayObject3D.h"
#include "ParticleSystem.h"

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

	//remove the display
	size = mDisplayPoints.size();
	for (i = 0; i < size; i++)
	{
		delete mDisplayPoints[i];
	}
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
	mDisplayPoints = vector<DisplayObject3D*>();
	mDisplayLines = vector<DisplayObject3D*>();

	mParticles = vector<Particle*>();
	mLinks = vector<ParticleLink*>();

	switch(mGeometryType)
	{
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

#pragma region Create Line
void MassAggregate::CreateBodyLine(MassAggregateModels* models)
{
	Particle* particle;
	ParticleRod* rod;
	DisplayObject3D* objParticle;
	DisplayObject3D* objLink;

	//create the graphics particles
	objParticle = new DisplayObject3D(models->modelParticle);
	objParticle->getTransform()->SetPosition(mInitialPosition);
	mDisplayPoints.push_back(objParticle);

	objParticle = new DisplayObject3D(models->modelParticle);
	objParticle->getTransform()->SetPosition(mInitialPosition + Vector3f::unitX);
	mDisplayPoints.push_back(objParticle);

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
	mLinks.push_back((ParticleLink*)rod);

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
void MassAggregate::AddToParticleSystem(ParticleSystem* system)
{
	unsigned int i;
	unsigned int size;

	size = mParticles.size();
	for (i = 0; i < size; i++)
	{
		system->AddParticle(mParticles[i]);
	}
	size = mLinks.size();
	for (i = 0; i < size; i++)
	{
		system->AddContactGenerator(mLinks[i]);
	}
}
void MassAggregate::RemoveFromParticleSystem(ParticleSystem* system)
{
	unsigned int i;
	unsigned int size;

	size = mParticles.size();
	for (i = 0; i < size; i++)
	{
		system->RemoveFromSystem(mParticles[i]);
	}
	size = mLinks.size();
	for (i = 0; i < size; i++)
	{
		system->RemoveContactGenerator(mLinks[i]);		
	}
}


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
}