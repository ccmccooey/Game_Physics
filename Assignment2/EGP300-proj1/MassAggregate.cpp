#include "MassAggregate.h"
#include "ParticleRod.h"
#include "Particle.h"
#include "DisplayObject3D.h"
#include "GameObject.h"
#include "GameObjectLink.h"
#include "DebugLogger.h"

using namespace std;

//constructors
MassAggregate::MassAggregate()
{
	mGeometryType = MA_DEFAULT_GEOMETRY;
	mInitialPosition = MA_DEFAULT_POSITION;
	CreateBody();
}
MassAggregate::MassAggregate(MassAggregateGeometry geometry)
{
	mGeometryType = geometry;
	mInitialPosition = MA_DEFAULT_POSITION;
	CreateBody();
}
MassAggregate::MassAggregate(MassAggregateGeometry geometry, const Vector3f &position)
{
	mGeometryType = geometry;
	mInitialPosition = position;
	CreateBody();
}
MassAggregate::MassAggregate(MassAggregateGeometry geometry, float initialX, float initialY, float initialZ)
{
	mGeometryType = geometry;
	mInitialPosition = Vector3f(initialX, initialY, initialZ);
	CreateBody();
}
MassAggregate::MassAggregate(const MassAggregate &rhs)
{
	mGeometryType = rhs.mGeometryType;
	mInitialPosition = rhs.mInitialPosition;
	CreateBody();
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
Particle* MassAggregate::GetParticleLast() const
{
	if (mParticles.size() > 0)
		return mParticles[mParticles.size() - 1]->GetPhysicsObject();
	return nullptr;
}
DisplayObject3D* MassAggregate::GetGraphicsObjectAt(unsigned int index) const
{
	if (index >= 0 && index < mParticles.size())
	{
		return mParticles[index]->GetGraphicsObject();
	}
	return nullptr;
}

//creating the geometry
void MassAggregate::CreateBody()
{
	mAddedToSystems = false;

	mParticles = vector<GameObject*>();
	mLinks = vector<GameObjectLink*>();

	switch(mGeometryType)
	{
	case MassAggregateGeometry::MA_Point:
		CreateBodyPoint();
		break;
	case MassAggregateGeometry::MA_Solid_Line:
		CreateBodyLine();
		break;
	case MassAggregateGeometry::MA_Solid_Cube:
		CreateBodyCube();
		break;
	case MassAggregateGeometry::MA_Solid_Tetrahedron:
		CreateBodyTetrahedron();
		break;
	case MassAggregateGeometry::MA_Solid_PyramidWithTop:
		CreateBodyPyramidWithTop();
		break;
	}
}

void MassAggregate::InsertParticle(const Vector3f &relativePosition)
{
	GameObject* obj = new GameObject("Cube", "ParticleMetal", mInitialPosition + relativePosition);
	mParticles.push_back(obj);
}
void MassAggregate::InsertParticle(GameObject* obj)
{
	mParticles.push_back(obj);
}
void MassAggregate::InsertLink(int particleIndexA, int particleIndexB, LinkTypes type)
{
	if (type == LinkTypes::Rod)
	{
		ParticleRod* rod = new ParticleRod(8.0f);
		rod->mParticleA = mParticles[particleIndexA]->GetPhysicsObject();
		rod->mParticleB = mParticles[particleIndexB]->GetPhysicsObject();
		GameObjectLink* link = new GameObjectLink("Cube", "SteelRod", rod);		
		mLinks.push_back(link);
	}
}

#pragma region Create Point
void MassAggregate::CreateBodyPoint()
{
	InsertParticle(mInitialPosition);
}
#pragma endregion
#pragma region Create Line
void MassAggregate::CreateBodyLine()
{
	InsertParticle(Vector3f::zero);
	InsertParticle(Vector3f::unitX * 10.0f +Vector3f::unitY * 5.0f);
	InsertLink(0, 1, LinkTypes::Rod);
}
#pragma endregion
#pragma region Create Tetrahedron
void MassAggregate::CreateBodyTetrahedron()
{
	float v = 5.0f;
	float h = v * 0.5f;
	InsertParticle(Vector3f(-h, 0.0f, 0.0f));
	InsertParticle(Vector3f(h, 0.0f, 0.0f));
	InsertParticle(Vector3f(0.0f, 0.0f, -v));
	InsertParticle( Vector3f(0.0f, v, -h));

	InsertLink(0, 1, LinkTypes::Rod);
	InsertLink(1, 2, LinkTypes::Rod);
	InsertLink(2, 0, LinkTypes::Rod);
	InsertLink(0, 3, LinkTypes::Rod);
	InsertLink(1, 3, LinkTypes::Rod);
	InsertLink(2, 3, LinkTypes::Rod);
}
#pragma endregion
#pragma region Create Cube
void MassAggregate::CreateBodyCube()
{
	float d = 5.0f;

	//bottom square particles
	InsertParticle(Vector3f(0.0f, 0.0f, 0.0f));
	InsertParticle(Vector3f(d, 0.0f, 0.0f));
	InsertParticle(Vector3f(d, 0.0f, d));
	InsertParticle(Vector3f(0.0f, 0.0f, d));
	//top square particles
	InsertParticle(Vector3f(0.0f, d, 0.0f));
	InsertParticle(Vector3f(d, d, 0.0f));
	InsertParticle(Vector3f(d, d, d));
	InsertParticle(Vector3f(0.0f, d, d));

	//bottom square links
	InsertLink(0, 1, LinkTypes::Rod);
	InsertLink(1, 2, LinkTypes::Rod);
	InsertLink(2, 3, LinkTypes::Rod);
	InsertLink(3, 0, LinkTypes::Rod);

	//top square links
	InsertLink(4, 5, LinkTypes::Rod);
	InsertLink(5, 6, LinkTypes::Rod);
	InsertLink(6, 7, LinkTypes::Rod);
	InsertLink(7, 4, LinkTypes::Rod);

	//connecting the bottom and top squares
	InsertLink(0, 4, LinkTypes::Rod);
	InsertLink(1, 5, LinkTypes::Rod);
	InsertLink(2, 6, LinkTypes::Rod);
	InsertLink(3, 7, LinkTypes::Rod);
}
#pragma endregion
#pragma region Create Pyrmaid with Top
void MassAggregate::CreateBodyPyramidWithTop()
{
	float v = 5.0f;
	float h = v * 0.5f;
	InsertParticle(Vector3f(-h, 0.0f, h));
	InsertParticle(Vector3f(h, 0.0f, h));
	InsertParticle(Vector3f(h, 0.0f, -h));
	InsertParticle(Vector3f(-h, 0.0f, -h));
	InsertParticle(Vector3f(0.0f, v, 0.0f));
	InsertParticle(Vector3f(0.0f, v + v, 0.0f));

	InsertLink(0, 1, LinkTypes::Rod);
	InsertLink(1, 2, LinkTypes::Rod);
	InsertLink(2, 3, LinkTypes::Rod);
	InsertLink(3, 0, LinkTypes::Rod);

	InsertLink(0, 4, LinkTypes::Rod);
	InsertLink(1, 4, LinkTypes::Rod);
	InsertLink(2, 4, LinkTypes::Rod);
	InsertLink(3, 4, LinkTypes::Rod);

	InsertLink(4, 5, LinkTypes::Rod);
	
}
#pragma endregion

//adding new particles
void MassAggregate::ConnectParticle(GameObject* existingParticle, int connectToIndex, LinkTypes linkType)
{
	InsertParticle(existingParticle);
	if (connectToIndex < 0)
		connectToIndex = 0;
	if (connectToIndex >= (int)mParticles.size() - 1)
		connectToIndex = (int)mParticles.size() - 2;

	InsertLink(mParticles.size() - 1, connectToIndex, LinkTypes::Rod); //connects a the most recently added particle to another particle represented by and index
}

//linking the positions
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

//adding force to all the particles in the mass aggregates
void MassAggregate::AddForce(const Vector3f &force)
{
	unsigned int i;
	unsigned int size;
	Particle* particle;

	size = mParticles.size();
	for (i = 0; i < size; i++)
	{
		particle = mParticles[i]->GetPhysicsObject();
		if (particle != nullptr)
			particle->AddForce(force);
	}
}