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
	UpdateRenderPosition();
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
Vector3f Particle::GetPosition() const
{
	return mPosition;
}
Vector3f Particle::GetVelocity() const
{
	return mVelocity;
}
Vector3f Particle::GetAcceleration() const
{
	return mAcceleration;
}
Vector3f Particle::GetForce() const
{
	return mAccumulatedForce;
}
float Particle::GetMass() const
{
	return mMass;
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
	UpdateRenderPosition();
}
void Particle::SetPosition(float x, float y, float z)
{
	mPosition.Set(x, y, z);
	UpdateRenderPosition();
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
	UpdateRenderPosition();
}
void Particle::UpdateRenderPosition()
{
	mTransform->SetPosition(mPosition * DISTANCE_SCALE);
}

//fixed update occuring at a fixed framerate
void Particle::FixedUpdate(double t)
{
	mAcceleration = mAccumulatedForce * mInverseMass;
	
	mVelocity = mVelocity + mAcceleration * (float)t;

	mPosition += mVelocity * (float)t;

	
	
	

	//mTransform->Translate(mVelocity);
	
	if (mVelocity != Vector3f::zero)
	{
		UpdateRenderPosition();
	}
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
