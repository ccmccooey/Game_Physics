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
private:
	float mMass;
	float mMassPerUnit;
	float mSize;
	std::string mName;

public:
	ObjectMaterial();
	ObjectMaterial(float massPerUnit, float size, const std::string &name);
	ObjectMaterial(const ObjectMaterial &rhs);
	~ObjectMaterial();

	//accessors
	float GetMass() const;
	float GetMassPerUnit() const;
	float GetSize() const;
	std::string const& GetName() const;

	//setters
	void SetMassPerUnit(float mass);
	void SetSize(float size);
	void SetName(const std::string &name);
	ObjectMaterial& operator = ( const ObjectMaterial& rhs );
	void SetObjectType(const std::string &name, float massPerUnit, float size);

private:
	void CalculateMass();

};

#endif