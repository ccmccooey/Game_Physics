#include "Model.h"
#include "Planet.h"
#include "Transform.h"


Planet::Planet(Model* model)
	:DisplayObject3D(model)
{
	mRigidBody = new Rigidbody(mTransform);
	mName = "no name";

}
Planet::~Planet()
{
	delete mRigidBody;
}


void Planet::FixedUpdate()
{
	mRigidBody->FixedUpdate();
}

Rigidbody* Planet::GetRigidBody() const
{
	return mRigidBody;
}


void Planet::SetName(const std::string &name)
{
	mName = name;
}