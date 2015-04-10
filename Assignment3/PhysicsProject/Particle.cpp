#include "Particle.h"
#include "Transform.h"
#include "ScaleFactor.h"

//constructors
Particle::Particle(Transform* transform)
{
	mTransform = transform;

	mPosition = Vector3f();
	mVelocity = Vector3f();
	mAccumulatedForce = Vector3f();
	mAcceleration = Vector3f();
	SetMass(1.0f);
}
Particle::Particle(Transform* transform, const Particle &rhs)
{
	mTransform = transform;
	CopyDataFrom(rhs);
}
Particle::Particle(const Particle &rhs)
{
	CopyDataFrom(rhs);
}
Particle::~Particle()
{
	
}

//accessros
Vector3f const& Particle::GetPosition() const
{
	return mPosition;
}
Vector3f const &Particle::GetVelocity() const
{
	return mVelocity;
}
Vector3f const &Particle::GetAcceleration() const
{
	return mAcceleration;
}
Vector3f const &Particle::GetForce() const
{
	return mAccumulatedForce;
}
float Particle::GetMass() const
{
	return mMass;
}
float Particle::GetInverseMass() const
{
	return mInverseMass;
}

//setters
void Particle::SetMass(float mass)
{
	mMass = mass;
	mInverseMass = 1.0f / mMass;
}
void Particle::SetVelocity(const Vector3f &velocity)
{
	mVelocity = velocity;
}
void Particle::SetPosition(const Vector3f &position)
{
	mPosition = position;
}
void Particle::SetPosition(float x, float y, float z)
{
	mPosition.Set(x, y, z);
}
void Particle::AddVelocity(const Vector3f &velocity)
{
	mVelocity += velocity;
}
void Particle::CopyDataFrom(const Particle &other)
{
	mPosition = other.mPosition;
	mVelocity = other.mVelocity;
	mAcceleration = other.mAcceleration;
	mMass = other.mMass;
	mInverseMass = other.mInverseMass;
}

//fixed update occuring at a fixed framerate
void Particle::FixedUpdate(double t)
{
	mAcceleration = mAccumulatedForce * mInverseMass;
	
	mVelocity = mVelocity + mAcceleration * (float)t;

	mPosition += mVelocity * (float)t;

	FinishUpdate();
}
void Particle::FinishUpdate()
{
	mAccumulatedForce = Vector3f::zero;
}


//adding force
void Particle::AddForce(const Vector3f &force)
{
	mAccumulatedForce += force;
}
void Particle::Translate(const Vector3f &translation)
{
	mPosition += translation;
}
void Particle::Translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}
