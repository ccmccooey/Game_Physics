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
	Vector3f mPreviousAcceleration; //the acceleration of the rigid body on the previous frame
	Vector3f mAccumulatedForce;
	Vector3f mAccumulatedTorque;
	Quaternion mOrientation;
	Vector3f mAngularVelocity;
	Vector3f mAngularAcceleration;
	Matrix33f mInverseInertiaTensor;
	Matrix33f mInverseInertiaTensorWorld;
 
	// Derived data: computed from orientation
	Matrix44f mTransformMatrix;


	float mMass;
	float mInverseMass;
	bool mStatic; //static objects do not move and are unaffected by the physics of other objects

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
	Vector3f const& GetPreviousFrameAcceleration() const;
	Vector3f const& GetForce() const;
	Vector3f const& GetAngularVelocity() const;
	Vector3f const& GetAngularAcceleration() const;
	Quaternion const& GetOrientation() const;
	Vector3f const& GetRotation() const;
	Vector3f GetRotationVector() const;
	float GetMass() const;
	float GetInverseMass() const;
	bool IsStatic() const;
	Matrix44f const& GetTransformMatrix() const;
	Matrix33f GetInertiaTensorWorld() const;
	Vector3f GetPositionInWorldSpace(const Vector3f &position) const;
	Vector3f GetPositionInLocalSpace(const Vector3f &position) const;

	//inertia tensor accessor functions using output variables
	void GetInertiaTensorWorld(Matrix33f *inertiaTensorOut) const; 
	void GetInverseInertiaTensorWorld(Matrix33f *inverseInertiaTensorOut) const;

	//conerting to a string
	std::string ToString() const;	

	//setters
	void CopyDataFrom(const RigidBody &other);
	void SetVelocity(const Vector3f &velocity);
	void SetPosition(const Vector3f &position);
	void SetPosition(float x, float y, float z);
	void SetAngularVelocity(const Vector3f &angleVelocity);
	void SetOrientation(const Quaternion &orientation);
	void SetMass(float mass);
	void SetStatic(bool isStatic);
	void SetIntertiaTensor(const Matrix33f &intertiaTensor);
	void CalculateDerivedData();

	//movement
	void AddVelocity(const Vector3f &velocity);
	void AddAcceleration(const Vector3f &acceleration);
	void AddRotation(const Vector3f &rotation);
	void AddForce(const Vector3f &force);
	void AddTorque(const Vector3f &torque);
	void AddForceAtLocalPosition(const Vector3f &force, const Vector3f &point);
	void AddForceAtPosition(const Vector3f &force, const Vector3f &point);
	void Translate(const Vector3f &translation);
	void Translate(float x, float y, float z);

private:
	//updating the transform
	void CalculateTransformMatrix();

	static inline void TransformInertiaTensor(Matrix33f &iitWorld, const Quaternion &q, const Matrix33f &iitBody, const Matrix44f &rotmat);
};

#endif