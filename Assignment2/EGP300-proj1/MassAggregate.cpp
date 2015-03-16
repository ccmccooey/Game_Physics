#include "MassAggregate.h"


MassAggregate::MassAggregate()
{
	mGeometryType = MA_DEFAULT_GEOMETRY;
}
MassAggregate::MassAggregate(MassAggregateGeometry geometry)
{
	mGeometryType = geometry;
}
MassAggregate::MassAggregate(const MassAggregate &rhs)
{
	mGeometryType = rhs.mGeometryType;
}
MassAggregate::~MassAggregate()
{

}

//accessors
void MassAggregate::CreateBody()
{

}