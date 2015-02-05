#include "Model.h"
#include "Planet.h"
#include "Transform.h"

//constructor
Planet::Planet(Model* model)
	:DisplayObject3D(model)
{
	mRigidBody = new Rigidbody(mTransform);
	mName = "no name";

}
Planet::~Planet()
{
	delete mRigidBody;
	mRigidBody = nullptr;
}


void Planet::FixedUpdate(double t)
{
	mRigidBody->FixedUpdate(t);
}

//accessors
Rigidbody* Planet::GetRigidBody() const
{
	return mRigidBody;
}
std::string Planet::GetName() const
{
	return mName;
}

//setters
void Planet::SetName(const std::string &name)
{
	mName = name;
}
