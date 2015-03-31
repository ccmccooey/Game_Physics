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
	MassAggregate();
	MassAggregate(MassAggregateGeometry geometry);
	MassAggregate(MassAggregateGeometry geometry, const Vector3f &position);
	MassAggregate(MassAggregateGeometry geometry, float initialX, float initialY, float initialZ);
	MassAggregate(const MassAggregate &rhs);
	~MassAggregate();

	//accessors
	Particle* GetParticleAt(unsigned int index) const;
	Particle* GetParticleLast() const;
	DisplayObject3D* GetGraphicsObjectAt(unsigned int index) const;

	//setters
	void LinkPositions(); //link the position of the graphics object from the physics object
	void InsertParticle(const Vector3f &relativePosition);
	void InsertParticle(GameObject* existingParticle);
	void InsertLink(int particleIndexA, int particleIndexB, LinkTypes type);

	//add objects and remove objects
	void ConnectParticle(GameObject* existingParticle, int connectToIndex, LinkTypes linkType);

	//adds force to the objects
	void AddForce(const Vector3f &force);

private:
	void CreateBody();
	void CreateBodyPoint();
	void CreateBodyLine();
	void CreateBodyCube();
	void CreateBodyTetrahedron();
	void CreateBodyPyramidWithTop();

	//adding and removing to systems
	//void AddToSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
	//void DeleteFromSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
};


#endif