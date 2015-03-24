#include "GameObjectLink.h"
#include "DisplayObject3DManager.h"
#include "ParticleLink.h"
#include "DisplayObject3D.h"
#include "ScaleFactor.h"
#include "SimpleMath.h"
#include "Vector2f.h"

//constructors
GameObjectLink::GameObjectLink(Model* model, ParticleLink *link)
{
	mGraphicsObject = new DisplayObject3D(model);
	mPhysicsLink = link;
}
GameObjectLink::GameObjectLink(const GameObjectLink &rhs)
{

}
GameObjectLink::~GameObjectLink()
{
	
}

//accessors
ParticleLink* GameObjectLink::GetLink() const
{
	return mPhysicsLink;
}
DisplayObject3D* GameObjectLink::GetGraphicsObject() const
{
	return mGraphicsObject;
}

//linking the position
void GameObjectLink::LinkPositions() //link the position of the graphics object from the physics object
{
	Transform* pTransform = mGraphicsObject->getTransform();
	if (pTransform != nullptr && mPhysicsLink != nullptr)
	{
		const Vector3f &a = mPhysicsLink->GetPositionA();
		const Vector3f &b = mPhysicsLink->GetPositionB();
		Vector3f position = Vector3f::Midpoint(a, b);

		pTransform->SetPosition(position * DISTANCE_SCALE);

		float distance = Vector3f::Distance(a, b);
		pTransform->SetScale(distance * DISTANCE_SCALE, 0.25f, 0.25f);

		float rotX = Vector2f::AngleBetweenRadians(Vector2f(a.z, a.y), Vector2f(b.z, b.y));
		float rotY = Vector2f::AngleBetweenRadians(Vector2f(a.x, a.z), Vector2f(b.x, b.z));
		float rotZ = Vector2f::AngleBetweenRadians(Vector2f(a.x, a.y), Vector2f(b.x, b.y));
		
		pTransform->SetRotationRadians(rotX, rotY, rotZ);
	}
}