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
	mAccumulatedTorque = Vector3f();
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
	mAccumulatedTorque = Vector3f();
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
Matrix44f const& RigidBody::GetTransformMatrix() const
{
	return mTransformMatrix;
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
Vector3f RigidBody::GetPositionInWorldSpace(const Vector3f &position) const
{
	return mTransformMatrix.Transform(position);	
}
Vector3f RigidBody::GetPositionInLocalSpace(const Vector3f &position) const
{
	return mTransformMatrix.TransformInverse(position);
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
	mTransformMatrix[3] = mPosition.x;
	mTransformMatrix[7] = mPosition.y;
	mTransformMatrix[11] = mPosition.z;
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
	mAccumulatedTorque = other.mAccumulatedTorque;
	mOrientation = other.mOrientation;
	mAngularVelocity = other.mAngularVelocity;
	mTransformMatrix = other.mTransformMatrix;
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
void RigidBody::CalculateDerivedData()
{
    mOrientation.normalize();

    // Calculate the transform matrix for the body.
	CalculateTransformMatrix();

    // Calculate the inertiaTensor in world space.
    TransformInertiaTensor(mInverseInertiaTensorWorld, mOrientation, mInverseInertiaTensor, mTransformMatrix);
}

//movement
void RigidBody::AddVelocity(const Vector3f &velocity)
{
	mVelocity += velocity;
}
void RigidBody::AddRotation(const Vector3f &rotation)
{
	mRotation += rotation;
	CalculateTransformMatrix();
}
void RigidBody::AddTorque(const Vector3f &torque)
{
	mAccumulatedTorque += torque;
}
void RigidBody::AddForce(const Vector3f &force)
{
	mAccumulatedForce += force;
}
void RigidBody::AddForceAtLocalPosition(const Vector3f &force, const Vector3f &point)
{
	// Convert to coordinates relative to center of mass.
	Vector3f pt = GetPositionInWorldSpace(point); 
	AddForceAtPosition(force, pt);
}

void RigidBody::AddForceAtPosition(const Vector3f &force, const Vector3f &point)
{
	// Convert to coordinates relative to center of mass.
	Vector3f pt = point - mPosition;

	mAccumulatedForce += force;
	mAccumulatedTorque += Vector3f::CrossProduct(pt, force);
	//isAwake = true;
}
void RigidBody::Translate(const Vector3f &translation)
{
	mPosition += translation;
	CalculateTransformMatrix();
}
void RigidBody::Translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
	CalculateTransformMatrix();
}


//transform function (from book too much going on)
inline void RigidBody::TransformInertiaTensor(Matrix33f &iitWorld, const Quaternion &q, const Matrix33f &iitBody, const Matrix44f &rotmat)
{
    float t4 = rotmat[0] * iitBody[0] + rotmat[1] * iitBody[3] + rotmat[2] * iitBody[6];
    float t9 = rotmat[0] * iitBody[1] + rotmat[1] * iitBody[4] + rotmat[2] * iitBody[7];
    float t14 = rotmat[0] * iitBody[2] + rotmat[1] * iitBody[5] + rotmat[2] * iitBody[8];
    float t28 = rotmat[4] * iitBody[0] + rotmat[5] * iitBody[3] + rotmat[6] * iitBody[6];
    float t33 = rotmat[4] * iitBody[1] + rotmat[5] * iitBody[4] + rotmat[6] * iitBody[7];
    float t38 = rotmat[4] * iitBody[2] + rotmat[5] * iitBody[5] + rotmat[6] * iitBody[8];
    float t52 = rotmat[8] * iitBody[0] + rotmat[9] * iitBody[3] + rotmat[10] * iitBody[6];
    float t57 = rotmat[8] * iitBody[1] + rotmat[9] * iitBody[4] + rotmat[10] * iitBody[7];
    float t62 = rotmat[8] * iitBody[2] + rotmat[9] * iitBody[5] + rotmat[10] * iitBody[8];

    iitWorld[0] = t4 * rotmat[0] + t9 * rotmat[1] + t14 * rotmat[2];
    iitWorld[1] = t4 * rotmat[4] + t9 * rotmat[5] + t14 * rotmat[6];
    iitWorld[2] = t4 * rotmat[8] + t9 * rotmat[9] + t14 * rotmat[10];
    iitWorld[3] = t28 * rotmat[0] + t33 * rotmat[1] + t38 * rotmat[2];
    iitWorld[4] = t28 * rotmat[4] + t33 * rotmat[5] + t38 * rotmat[6];
    iitWorld[5] = t28 * rotmat[8] + t33 * rotmat[9] + t38 * rotmat[10];
    iitWorld[6] = t52 * rotmat[0] + t57 * rotmat[1] + t62 * rotmat[2];
    iitWorld[7] = t52 * rotmat[4] + t57 * rotmat[5] + t62 * rotmat[6];
    iitWorld[8] = t52 * rotmat[8] + t57 * rotmat[9] + t62 * rotmat[10];
}

//update
void RigidBody::FixedUpdate(double t)
{
	//keep track of the acceleration on the previous frame
	mPreviousAcceleration = mAcceleration;

	//calculate linear acceleration
	mAcceleration = mAccumulatedForce * mInverseMass;
	
	//Calculate angular acceleration
	mAngularAcceleration = mInverseInertiaTensorWorld.Transform(mAccumulatedTorque);

	//Calculate angular velocity
	mRotation += mAngularAcceleration * (float)t;
	
	//Calculate linear velocity
	mVelocity = mVelocity + mAcceleration * (float)t;

	// rotate the object based on angular velocity.
    mOrientation.addScaledVector(mRotation, (float)t);

	//move the object based on linear velocity
	mPosition += mVelocity * (float)t;

	CalculateDerivedData();

	//zero out the accumulated force and accumulated torque
	FinishUpdate();
}
void RigidBody::FinishUpdate()
{
	mAccumulatedForce = Vector3f::zero;
	mAccumulatedTorque = Vector3f::zero;
}