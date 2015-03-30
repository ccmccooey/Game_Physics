#include "GameObjectLink.h"
#include "DisplayObject3DManager.h"
#include "ParticleSystem.h"
#include "ParticleLink.h"
#include "DisplayObject3D.h"
#include "MainApp.h"
#include "ScaleFactor.h"
#include "SimpleMath.h"
#include "Vector2f.h"

//constructors
GameObjectLink::GameObjectLink(Model* model, ParticleLink *link)
{
	mGraphicsObject = new DisplayObject3D(model);
	mPhysicsLink = link;

	MainApp::GetGraphicsSystem()->AddObject(mGraphicsObject);
	MainApp::GetPhysicsSystem()->AddContactGenerator(mPhysicsLink);
}
GameObjectLink::GameObjectLink(const GameObjectLink &rhs)
{

}
GameObjectLink::~GameObjectLink()
{
	MainApp::GetGraphicsSystem()->RemoveObject(mGraphicsObject);
	MainApp::GetPhysicsSystem()->RemoveContactGenerator(mPhysicsLink);
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
		
		/*
		//Attempt 1 FUCK FAIL
		float rotX = Vector2f::AngleBetweenRadians(Vector2f(a.y, -a.z), Vector2f(b.y, -b.z));
		float rotY = Vector2f::AngleBetweenRadians(Vector2f(a.x, a.z), Vector2f(b.x, b.z));
		float rotZ = Vector2f::AngleBetweenRadians(Vector2f(b.x, b.y), Vector2f(a.x, a.y));
		pTransform->SetRotationRadians(rotX, rotY, rotZ);
		*/	

		/* 
		//Attemt 2 FUCK FAIL
		Vector3f lookAt = Vector3f::DirectionTo(b, a);		
		float r = lookAt.Length();
		float theta = acosf(lookAt.z / r);
		float phi = atan2f(lookAt.y, lookAt.x);
		pTransform->SetRotationRadians(theta, phi, 0.0f);
		*/
		
		/*
		//Attempt 3 FUCK FAIL		
		Vector3f lookAt = Vector3f::DirectionTo(b, a);	
		float rotX = atan2f( lookAt.y, lookAt.z );
		float rotY = atan2f( lookAt.x * cosf(rotX), lookAt.z );
		float rotZ = atan2f( cosf(rotX), sinf(rotX) * sinf(rotY) );
		pTransform->SetRotationRadians(rotX, -rotY, -rotZ);
		*/

		/*
		//Attempt 4 FUCK FAIL
		Vector3f lookAt = Vector3f::DirectionTo(b, a);	
		float rotX = 0.0f;
		float rotY = atan2f(lookAt.z, lookAt.x);
		float rotZ = atan2f(lookAt.y, sqrtf(lookAt.x*lookAt.x + lookAt.z*lookAt.z));
		pTransform->SetRotationRadians(rotX, rotY, rotZ);
		*/


		//Attempt 5 FUCK FAIL
		Vector3f lookAt = Vector3f::DirectionTo(b, a);
		float rotX = atan2f(sqrtf(pow(lookAt.x, 2) + pow(lookAt.z, 2)), lookAt.y);
		float rotY = atan2f(lookAt.x, lookAt.z);	
		float rotZ = 0.0f;
		pTransform->SetRotationRadians(rotX, rotY - 1.5707963267948966192313f, rotZ);

		//Set the scale
		float distance = Vector3f::Distance(a, b);
		pTransform->SetScale(distance * DISTANCE_SCALE, 0.25f, 0.25f);
	}
}