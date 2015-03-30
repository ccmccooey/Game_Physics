#ifndef _MASS_AGGREGATE_H
#define _MASS_AGGREGATE_H

#include <vector>
#include "Vector3f.h"
#include "MassAggregateGeometry.h"
#include "MassAggregateModels.h"

#define MA_DEFAULT_GEOMETRY MassAggregateGeometry::MA_Solid_Line
#define MA_DEFAULT_POSITION Vector3f::zero

class DisplayObject3D;
class DisplayObject3DManager;
class GameObjectLink;
class GameObject;
class Particle;
class ParticleSystem;
/*
class AggregateFactory 
{
public:
	virtual ~AggregateFactory() {}
	virtual MassAggregate* BuildAggregate() = 0;
};

class CubeBuilder : public AggregateFactory 
{
public:
	virtual MassAggregate* BuildAggregate() 
	{
		MassAggregate* aggregate = new MassAggregate(...);
		aggregate.addLink(...);
		aggregate.addParticle(...);
		return aggregate;
	};
};

enum 
{
	BUILD_CUBE = 0,
	BUILD_TETRA,
	BUILD_RING,
	BUILD_CLOTH,
	NUM_BUILDERS
};
AggregateFactory *kAggregates[NUM_BUILDERS] = 
{
	new CubeBuilder(...),
	new TetraBuilder(...),
	new ClothBuilder(...)
};

MassAggregate* myAggregate = kAggregates[BUILD_CUBE]->BuildAggregate();*/

class MassAggregate
{
private:
	enum LinkTypes
	{
		Rod = 0,
		Cable,
	};
private:
	std::vector<GameObject*> mParticles;
	std::vector<GameObjectLink*> mLinks;

	MassAggregateGeometry mGeometryType;
	Vector3f mInitialPosition;
	bool mAddedToSystems;

public:
	MassAggregate(MassAggregateModels* models);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, const Vector3f &position);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, float initialX, float initialY, float initialZ);
	MassAggregate(MassAggregateModels* models, const MassAggregate &rhs);
	~MassAggregate();

	//accessors
	Particle* GetParticleAt(unsigned int index) const;
	DisplayObject3D* GetGraphicsObjectAt(unsigned int index) const;

	//setters
	void LinkPositions(); //link the position of the graphics object from the physics object
	void InsertParticle(Model* model, const Vector3f &relativePosition);
	void InsertLink(Model* model, int particleIndexA, int particleIndexB, LinkTypes type);

	//add objects and remove objects
	void CreateAndConnectParticle(GameObject* existingParticle, int connectToIndex, LinkTypes linkType, Model* linkModel, ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);

	//adds force to the objects
	void AddForce(const Vector3f &force);

private:
	void CreateBody(MassAggregateModels* models);
	void CreateBodyPoint(MassAggregateModels* models);
	void CreateBodyLine(MassAggregateModels* models);
	void CreateBodyCube(MassAggregateModels* models);
	void CreateBodyTetrahedron(MassAggregateModels* models);
	void CreateBodyPyramidWithTop(MassAggregateModels* models);

	//adding and removing to systems
	//void AddToSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
	//void DeleteFromSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
};


#endif