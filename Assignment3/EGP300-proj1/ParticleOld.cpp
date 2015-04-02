#include "ParticleOld.h"



ParticleOld::ParticleOld(Model* model)
:DisplayObject3D(model)
{
	mVelocity = Vector3f();
	mForce = Vector3f();
	mAcceleration = Vector3f();
}
ParticleOld::~ParticleOld()
{

}

void ParticleOld::FixedUpdate()
{
	mVelocity += mAcceleration;

	mTransform->Translate(mVelocity);
}

void ParticleOld::AddForce(const Vector3f &force)
{
	mForce += force;
}