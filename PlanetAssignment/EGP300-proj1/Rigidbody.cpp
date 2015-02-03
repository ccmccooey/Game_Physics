#include "RigidBody.h"
#include "Transform.h"

//constructors
Rigidbody::Rigidbody(Transform* transform)
{
	mTransform = transform;

	mPosition = mTransform->GetPosition();
	mVelocity = Vector3f();
	mForce = Vector3f();
	mAcceleration = Vector3f();
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
	mInverseMass = 1 / mMass;
}
void Rigidbody::SetVelocity(const Vector3f &velocity)
{
	mVelocity = velocity;
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

	mTransform->SetPosition(mPosition);
}

//fixed update
void Rigidbody::FixedUpdate()
{
	if (mTransform->GetPosition() != mPosition)
	{
		mTransform->SetPosition(mPosition);
	}

	mPosition += mVelocity;

	mVelocity += mAcceleration;

	mTransform->Translate(mVelocity);
}


//adding force
void Rigidbody::AddForce(const Vector3f &force)
{
	mForce += force;

	mAcceleration = force * mInverseMass;
}