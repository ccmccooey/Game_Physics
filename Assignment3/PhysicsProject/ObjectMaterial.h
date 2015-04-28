#ifndef _OBJECT_MATERIAL_H
#define _OBJECT_MATERIAL_H

//these may not be exaclty right
#define MASS_OBJECT_AIRFILLED 0.125f
#define MASS_OBJECT_PLASTIC 1.0f
#define MASS_OBJECT_WOOD 2.0f
#define MASS_OBJECT_STEEL 9.0f
#define MASS_OBJECT_IRON 10.0f

#define SIZE_OBJECT_SMALL 1.0f
#define SIZE_OBJECT_MEDIUM 2.5f
#define SIZE_OBJECT_LARGE 7.5f

#include <string>

struct ObjectMaterial
{
public:
	float mMass;
	float mSize;
	std::string mName;

public:
	ObjectMaterial();
	ObjectMaterial(float mass, float size, const std::string &name);
	ObjectMaterial(const ObjectMaterial &rhs);
	~ObjectMaterial();

	ObjectMaterial& operator = ( const ObjectMaterial& rhs );
	void SetObjectType(const std::string &name, float massPerUnit, float size);

};

#endif