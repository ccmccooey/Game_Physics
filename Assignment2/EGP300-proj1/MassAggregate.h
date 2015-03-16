#ifndef _MASS_AGGREGATE_H
#define _MASS_AGGREGATE_H

#include <vector>
#include "MassAggregateGeometry.h"

class DisplayObject3D;
class ParticleLink;
class Particle;
class ParticleSystem;

class MassAggregate
{
private:
	std::vector<DisplayObject3D*> mDisplayPoints;
	std::vector<DisplayObject3D*> mDisplayLines;
	MassAggregateGeometry mGeometryType;

public:
	MassAggregate();
	MassAggregate(MassAggregateGeometry geometry);
	MassAggregate(const MassAggregate &rhs);
	~MassAggregate();

	//accessors
	void AddToParticleSystem(ParticleSystem* system);
	void RemoveFromParticleSystem(ParticleSystem* system);

private:
	void CreateBody();

	
};


#endif