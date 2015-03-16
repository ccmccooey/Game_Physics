#ifndef _MASS_AGGREGATE_GEOMETRY_H
#define _MASS_AGGREGATE_GEOMETRY_H

enum MassAggregateGeometry
{
	Custom = 0,
	MA_Solid_Line,
	MA_Solid_Cube,
	MA_Solid_Tetrahedron
};

#define MA_DEFAULT_GEOMETRY MassAggregateGeometry::MA_Solid_Line

#endif