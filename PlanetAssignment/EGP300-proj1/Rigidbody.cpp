#include "RigidBody.h"
#include "Transform.h"
#include "PlanetScaleFactor.h"

//constructors
Rigidbody::Rigidbody(Transform* transform)
{
	mTransform = transform;

	mPosition = Vector3f();
	mVelocity = Vector3f();
	mForce = Vector3f();
	mAcceleration = Vector3f();
	UpdateRenderPosition();
}
Rigidbody::Rigidbody(Transform* transform, const Rigidbody &rhs)
{
	mTransform = transform;
	CopyDataFrom(rhs);
}
Rigidbody::Rigidbody(const Rigidbody &rhs)
{
	CopyDataFrom(rhs);
}
Rigidbody::~Rigidbody()
{
	
}

//accessros
Vector3f Rigidbody::GetPosition() const
{
	return mPosition;
}
Vector3f Rigidbody::GetVelocity() const
{
	return mVelocity;
}
Vector3f Rigidbody::GetAcceleration() const
{
	return mAcceleration;
}
Vector3f Rigidbody::GetForce() const
{
	return mForce;
}
float Rigidbody::GetMass() const
{
	return mMass;
}

//setters
void Rigidbody::SetMass(float mass)
{
	mMass = mass;
	mInverseMass = 1.0f / mMass;
}
void Rigidbody::SetVelocity(const Vector3f &velocity)
{
	mVelocity = velocity;
}
void Rigidbody::SetPosition(const Vector3f &position)
{
	mPosition = position;
	UpdateRenderPosition();
}
void Rigidbody::SetPosition(float x, float y, float z)
{
	mPosition.Set(x, y, z);
	UpdateRenderPosition();
}
void Rigidbody::AddVelocity(const Vector3f &velocity)
{
	mVelocity += velocity;
}
void Rigidbody::CopyDataFrom(const Rigidbody &other)
{
	mPosition = other.mPosition;
	mVelocity = other.mVelocity;
	mAcceleration = other.mAcceleration;
	mMass = other.mMass;
	mInverseMass = other.mInverseMass;
	UpdateRenderPosition();
}
void Rigidbody::UpdateRenderPosition()
{
	mTransform->SetPosition(mPosition * PLANET_DISTANCE_SCALE);
}

//fixed update
void Rigidbody::FixedUpdate(double t)
{
	mPosition += mVelocity * t;
	
	mVelocity = mVelocity + mAcceleration * t;

	mAcceleration = mForce * mInverseMass;

	
	
	

	//mTransform->Translate(mVelocity);
	
	if (mVelocity != Vector3f::zero)
	{
		UpdateRenderPosition();
	}
	FinishUpdate();
}
void Rigidbody::FinishUpdate()
{
	mForce = Vector3f::zero;

}


//adding force
void Rigidbody::AddForce(const Vector3f &force)
{
	mForce += force;
}
