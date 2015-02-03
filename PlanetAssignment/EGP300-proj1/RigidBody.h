#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Vector3f.h"

class Transform;

class Rigidbody
{
private:
	Vector3f mPosition;
	Vector3f mVelocity;
	Vector3f mAcceleration;
	Vector3f mForce;
	float mMass;
	float mInverseMass;
	Transform* mTransform;

public:
	Rigidbody(Transform* transform);
	Rigidbody(Transform* transform, const Rigidbody &rhs);
	Rigidbody(const Rigidbody &rhs);
	~Rigidbody();

	void FixedUpdate();


	//accessors
	Vector3f GetPosition() const;
	Vector3f GetVelocity() const;
	Vector3f GetAcceleration() const;
	Vector3f GetForce() const;
	float GetMass() const;

	//setters
	void CopyDataFrom(const Rigidbody &other);
	void SetVelocity(const Vector3f &velocity);
	void AddVelocity(const Vector3f &velocity);
	void SetMass(float mass);

	//adding force
	void AddForce(const Vector3f &force);

};

#endif