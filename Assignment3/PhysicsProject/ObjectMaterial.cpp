#include "ObjectMaterial.h"

//constructors
ObjectMaterial::ObjectMaterial()
{
	mMass = 1.0f;
	mSize = 1.0f;
	mName = "Some Material";
}
ObjectMaterial::ObjectMaterial(float mass, float size, const std::string &name)
{
	mMass = mass;
	mSize = size;
	mName = name;
}
ObjectMaterial::ObjectMaterial(const ObjectMaterial &rhs)
{
	mMass = rhs.mMass;
	mSize = rhs.mSize;
	mName = rhs.mName;
}
ObjectMaterial::~ObjectMaterial()
{

}

//operator overloads
ObjectMaterial& ObjectMaterial::operator = ( const ObjectMaterial& rhs )
{
	mMass = rhs.mMass;
	mSize = rhs.mSize;
	mName = rhs.mName;
	return (*this);
}

void ObjectMaterial::SetObjectType(const std::string &name, float massPerUnit, float size)
{
	mName = name;
	mMass = massPerUnit * size;
	mSize = size;
}