#include "Particle.h"



Particle::Particle(Model* model)
:DisplayObject3D(model)
{
	mVelocity = Vector3f();
	mForce = Vector3f();
	mAcceleration = Vector3f();
}
Particle::~Particle()
{

}

void Particle::FixedUpdate()
{
	mVelocity += mAcceleration;

	mTransform->Translate(mVelocity);
}

void Particle::AddForce(const Vector3f &force)
{
	mForce += force;
}