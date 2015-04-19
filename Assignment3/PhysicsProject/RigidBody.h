#ifndef _RIGID_BODY_H
#define _RIGID_BODY_H

#include <string>
#include "Matrix44f.h"
#include "Matrix33f.h"
#include "Vector3f.h"
#include "Quaternion.h"

class RigidBody
{
private:
	Vector3f mPosition;
	Vector3f mVelocity;
	Vector3f mAcceleration;
	Vector3f mAccumulatedForce;

	Quaternion mOrientation;
	Vector3f mAngularVelocity;
	Matrix33f mInverseInertiaTensor;
 
	// Derived data: computed from orientation
	Matrix44f mTransformMatrix;


	float mMass;
	float mInverseMass;

public:
	RigidBody();
	RigidBody(float mass, const Vector3f &initialPosition);
	RigidBody(const RigidBody &rhs);
	~RigidBody();

	//update
	void FixedUpdate(double t);
	void FinishUpdate();

	//accessors
	Vector3f const& GetPosition() const;
	Vector3f const& GetVelocity() const;
	Vector3f const& GetAcceleration() const;
	Vector3f const& GetForce() const;
	Vector3f const& GetAngularVelocity() const;
	Quaternion const& GetOrientation() const;
	Vector3f GetRotationVector() const;
	Matrix33f const& GetInverseInteriaTensor() const;
	float GetMass() const;
	float GetInverseMass() const;
	std::string ToString() const;

	//setters
	void CopyDataFrom(const RigidBody &other);
	void SetVelocity(const Vector3f &velocity);
	void SetPosition(const Vector3f &position);
	void SetPosition(float x, float y, float z);
	void SetAngularVelocity(const Vector3f &angleVelocity);
	void SetOrientation(const Quaternion &orientation);
	void SetMass(float mass);

	//movement
	void AddVelocity(const Vector3f &velocity);
	void AddForce(const Vector3f &force);
	void AddTorque(const Vector3f &torque);
	void Translate(const Vector3f &translation);
	void Translate(float x, float y, float z);
};

#endif