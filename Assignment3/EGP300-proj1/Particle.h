#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "Vector3f.h"

class Transform;

class Particle
{
private:
	Vector3f mPosition;
	Vector3f mVelocity;
	Vector3f mAcceleration;
	Vector3f mAccumulatedForce;
	float mMass;
	float mInverseMass;
	Transform* mTransform;

public:
	Particle(Transform* transform);
	Particle(Transform* transform, const Particle &rhs);
	Particle(const Particle &rhs);
	~Particle();

	void FixedUpdate(double t);
	void FinishUpdate();


	//accessors
	Vector3f const &GetPosition() const;
	Vector3f const &GetVelocity() const;
	Vector3f const &GetAcceleration() const;
	Vector3f const &GetForce() const;
	float GetMass() const;
	float GetInverseMass() const;

	//setters
	void CopyDataFrom(const Particle &other);
	void SetVelocity(const Vector3f &velocity);
	void AddVelocity(const Vector3f &velocity);
	void SetPosition(const Vector3f &position);
	void SetPosition(float x, float y, float z);
	void SetMass(float mass);

	//movement
	void AddForce(const Vector3f &force);
	void Translate(const Vector3f &translation);
	void Translate(float x, float y, float z);
};

#endif