#include "RigidBody.h"

RigidBody::RigidBody()
{
	mPosition = Vector3f();
	mVelocity = Vector3f();
	mAccumulatedForce = Vector3f();
	mAcceleration = Vector3f();
	mPreviousAcceleration = Vector3f();
	mAngularVelocity = Vector3f();
	mRotation = Vector3f();
	mOrientation = Quaternion();
	mTransformMatrix = Matrix44f();
	SetMass(1.0f);
}
RigidBody::RigidBody(float mass, const Vector3f &initialPosition)
{
	mPosition = initialPosition;
	mRotation = Vector3f();
	mVelocity = Vector3f();
	mAccumulatedForce = Vector3f();
	mAcceleration = Vector3f();
	mPreviousAcceleration = Vector3f();
	mAngularVelocity = Vector3f();
	mOrientation = Quaternion();
	mTransformMatrix = Matrix44f();
	SetMass(mass);
}
RigidBody::RigidBody(const RigidBody &rhs)
{
	CopyDataFrom(rhs);
}
RigidBody::~RigidBody()
{

}

//accessors
Vector3f const& RigidBody::GetPosition() const
{
	return mPosition;
}
Vector3f const& RigidBody::GetVelocity() const
{
	return mVelocity;
}
Vector3f const& RigidBody::GetAcceleration() const
{
	return mAcceleration;
}
Vector3f const& RigidBody::GetPreviousFrameAcceleration() const
{
	return mPreviousAcceleration;
}
Vector3f const& RigidBody::GetForce() const
{
	return mAccumulatedForce;
}
float RigidBody::GetMass() const
{
	return mMass;
}
float RigidBody::GetInverseMass() const
{
	return mInverseMass;
}
Vector3f const& RigidBody::GetAngularVelocity() const
{
	return mAngularVelocity;
}
Quaternion const& RigidBody::GetOrientation() const
{
	return mOrientation;
}
Vector3f RigidBody::GetRotationVector() const
{
	return mRotation;
}
Vector3f const& RigidBody::GetRotation() const
{
	return mRotation;
}
std::string RigidBody::ToString() const
{
	std::string str = "Mass: " + std::to_string(mMass) + ", Position: " +mPosition.ToString() + ", Velocity: " +mVelocity.ToString() + ", Acceleration: " +mAcceleration.ToString();
	return str;
}

//inertia tensor accessors
void RigidBody::GetInertiaTensorWorld(Matrix33f *inertiaTensor) const
{
    inertiaTensor->SetInverse(mInverseInertiaTensorWorld); //Matrix33f inverse function not implemented
}
void RigidBody::GetInverseInertiaTensorWorld(Matrix33f *inverseInertiaTensor) const
{
    *inverseInertiaTensor = mInverseInertiaTensorWorld;
}

// updating the transform
void RigidBody::CalculateTransformMatrix()
{
	mOrientation.toRotationMatrix(mTransformMatrix);
	mTransformMatrix[3] += mPosition.x;
	mTransformMatrix[7] += mPosition.y;
	mTransformMatrix[11] += mPosition.z;
}

//setters
void RigidBody::CopyDataFrom(const RigidBody &other)
{
	mPosition = other.mPosition;
	mVelocity = other.mVelocity;
	mAcceleration = other.mAcceleration;
	mMass = other.mMass;
	mInverseMass = other.mInverseMass;
	mRotation = other.mRotation;
	mOrientation = other.mOrientation;
	mAngularVelocity = other.mAngularVelocity;
}
void RigidBody::SetVelocity(const Vector3f &velocity)
{
	mVelocity = velocity;
}
void RigidBody::SetPosition(const Vector3f &position)
{
	mPosition = position;
}
void RigidBody::SetPosition(float x, float y, float z)
{
	mPosition.Set(x, y, z);
}
void RigidBody::SetMass(float mass)
{
	mMass = mass;
	mInverseMass = 1.0f / mass;
}
void RigidBody::SetAngularVelocity(const Vector3f &angleVelocity)
{
	mAngularVelocity = angleVelocity;
}
void RigidBody::SetOrientation(const Quaternion &orientation)
{
	mOrientation = orientation;
}

//movement
void RigidBody::AddVelocity(const Vector3f &velocity)
{
	mVelocity += velocity;
}
void RigidBody::AddTorque(const Vector3f &torque)
{

}
void RigidBody::AddForce(const Vector3f &force)
{
	mAccumulatedForce += force;
}
void RigidBody::Translate(const Vector3f &translation)
{
	mPosition += translation;
}
void RigidBody::Translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}
void RigidBody::FinishUpdate()
{
	mAccumulatedForce = Vector3f::zero;
}

//update
void RigidBody::FixedUpdate(double t)
{
	mPreviousAcceleration = mAcceleration;
	mAcceleration = mAccumulatedForce * mInverseMass;
	
	mVelocity = mVelocity + mAcceleration * (float)t;

	mPosition += mVelocity * (float)t;

	FinishUpdate();
}