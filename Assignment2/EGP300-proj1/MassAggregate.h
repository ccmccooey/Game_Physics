#ifndef _MASS_AGGREGATE_H
#define _MASS_AGGREGATE_H

#include <vector>
#include "Vector3f.h"
#include "MassAggregateGeometry.h"
#include "MassAggregateModels.h"

#define MA_DEFAULT_GEOMETRY MassAggregateGeometry::MA_Solid_Line
#define MA_DEFAULT_POSITION Vector3f::zero

class DisplayObject3D;
class ParticleLink;
class Particle;
class ParticleSystem;
struct MassAggregateModels;
struct DrawData;
/*
class AggregateFactory {
public:
	virtual ~AggregateFactory() {}
	virtual MassAggregate* BuildAggregate() = 0;
};

class CubeBuilder : public AggregateFactory {
public:
	virtual MassAggregate* BuildAggregate() {
		MassAggregate* aggregate = new MassAggregate(...);
		aggregate.addLink(...);
		aggregate.addParticle(...);
		return aggregate;
	};
};

enum {
	BUILD_CUBE = 0,
	BUILD_TETRA,
	BUILD_RING,
	BUILD_CLOTH,
	NUM_BUILDERS
};
AggregateFactory *kAggregates[NUM_BUILDERS] = {
	new CubeBuilder(...),
	new TetraBuilder(...),
	new ClothBuilder(...)
};

MassAggregate* myAggregate = kAggregates[BUILD_CUBE]->BuildAggregate();*/

class MassAggregate
{
private:
	std::vector<DisplayObject3D*> mDisplayPoints;
	std::vector<DisplayObject3D*> mDisplayLines;

	std::vector<Particle*> mParticles;
	std::vector<ParticleLink*> mLinks;

	MassAggregateGeometry mGeometryType;
	Vector3f mInitialPosition;

public:
	MassAggregate(MassAggregateModels* models);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, const Vector3f &position);
	MassAggregate(MassAggregateModels* models, MassAggregateGeometry geometry, float initialX, float initialY, float initialZ);
	MassAggregate(MassAggregateModels* models, const MassAggregate &rhs);
	~MassAggregate();

	//accessors
	void AddToParticleSystem(ParticleSystem* system);
	void RemoveFromParticleSystem(ParticleSystem* system);

	//setters

	//draw function
	void Draw(DrawData* drawData);

private:
	void CreateBody(MassAggregateModels* models);
	void CreateBodyLine(MassAggregateModels* models);
	void CreateBodyCube(MassAggregateModels* models);
	void CreateBodyTetrahedron(MassAggregateModels* models);
};


#endif