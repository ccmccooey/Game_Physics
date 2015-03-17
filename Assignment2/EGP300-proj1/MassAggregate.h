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