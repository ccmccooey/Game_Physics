#include "ObjectMaterial.h"

//constructors
ObjectMaterial::ObjectMaterial()
{
	mMassPerUnit = 1.0f;
	mSize = 1.0f;
	mName = "Some Material";
	CalculateMass();
}
ObjectMaterial::ObjectMaterial(float massPerUnit, float size, const std::string &name)
{
	mMassPerUnit = massPerUnit;
	mSize = size;
	mName = name;
	CalculateMass();
}
ObjectMaterial::ObjectMaterial(const ObjectMaterial &rhs)
{
	mMassPerUnit = rhs.mMassPerUnit;
	mMass = rhs.mMass;
	mSize = rhs.mSize;
	mName = rhs.mName;
}
ObjectMaterial::~ObjectMaterial()
{

}

//accessors
float ObjectMaterial::GetMass() const
{
	return mMass;
}
float ObjectMaterial::GetSize() const
{
	return mSize;
}
std::string const& ObjectMaterial::GetName() const
{
	return mName;
}

//setters
void ObjectMaterial::SetMassPerUnit(float mass)
{
	mMassPerUnit = mass;
	CalculateMass();
}
void ObjectMaterial::SetSize(float size)
{
	mSize = size;
	CalculateMass();
}
void ObjectMaterial::SetName(const std::string &name)
{
	mName = name;
}
void ObjectMaterial::CalculateMass()
{
	mMass = mMassPerUnit * mSize * mSize * mSize * 0.5f;
}

//operator overloads
ObjectMaterial& ObjectMaterial::operator = ( const ObjectMaterial& rhs )
{
	mMass = rhs.mMass;
	mMassPerUnit = rhs.mMassPerUnit;
	mSize = rhs.mSize;
	mName = rhs.mName;
	return (*this);
}

void ObjectMaterial::SetObjectType(const std::string &name, float massPerUnit, float size)
{
	mName = name;
	mMassPerUnit = massPerUnit;
	mSize = size;
	CalculateMass();
}