#include "GameObjectLink.h"
#include "MainApp.h"
#include "DisplayObject3DManager.h"
#include "ParticleSystem.h"
#include "ParticleLink.h"
#include "DisplayObject3D.h"
#include "ModelManager.h"
#include "MaterialManager.h"
#include "ScaleFactor.h"
#include "SimpleMath.h"
#include "Vector2f.h"
#include <iostream>

#define PI_OVER_2 1.5707963267948966192313216916398f

unsigned int GameObjectLink::msIDs = 0;

//constructors
GameObjectLink::GameObjectLink(const std::string &modelName, ParticleLink *link)
	:mID(msIDs)
{
	mGraphicsObject = new DisplayObject3D(MainApp::GetModelManager()->FindModel(modelName));
	mPhysicsLink = link;

	MainApp::GetGraphicsSystem()->AddObject(mGraphicsObject);
	MainApp::GetPhysicsSystem()->AddContactGenerator(mPhysicsLink);
	msIDs++;
}

GameObjectLink::GameObjectLink(const std::string &modelName, const std::string &materialName, ParticleLink *link)
	:mID(msIDs)
{
	mGraphicsObject = new DisplayObject3D(MainApp::GetModelManager()->FindModel(modelName));
	mGraphicsObject->SetMaterial(MainApp::GetMaterialManager()->FindMaterial(materialName));
	mPhysicsLink = link;

	MainApp::GetGraphicsSystem()->AddObject(mGraphicsObject);
	MainApp::GetPhysicsSystem()->AddContactGenerator(mPhysicsLink);
	msIDs++;
}

GameObjectLink::GameObjectLink(const GameObjectLink &rhs)
	:mID(msIDs)
{
	msIDs++;
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
		
		

		
		Vector3f v = b - a;

		//Attempt 1
		float rotX = 0.0f;
		float rotY = atan2f(v.z, v.x); //between 90 and -90 its screwed up
		float rotZ = atan2f(v.y, v.x);
		
		pTransform->SetRotationRadians(rotX, rotY, rotZ);

		/*
		if (mID == 0)
		{
			if (InputSystem::KeyDown(' '))
			{
				std::cerr << "RotY (" << rotY * (180.0f / 3.1415926f) << ") degrees" << std::endl;
			}
		}
		
		
		
		
		if (rotY > -PI_OVER_2 && rotY < PI_OVER_2)
		{
			rotY += PI_OVER_2 * PI_OVER_2;
			//std::cerr << "RotY (" << rotY * (180.0f / 3.1415926f) << ") degrees" << std::endl;
		}*/
		

		/*
		if (a.x < b.x)
		{
			rotY *= 1.0f;
		}*/
		
		//rotY = 0.0f;
		
		//pTransform->SetRotationRadians()
		

		/* 
		//Attemt 2
		Vector3f lookAt = Vector3f::DirectionTo(b, a);		
		float r = lookAt.Length();
		float theta = acosf(lookAt.z / r);
		float phi = atan2f(lookAt.y, lookAt.x);
		pTransform->SetRotationRadians(theta, phi, 0.0f);
		*/
		
		/*
		//Attempt 3		
		Vector3f lookAt = Vector3f::DirectionTo(b, a);	
		float rotX = atan2f( lookAt.y, lookAt.z );
		float rotY = atan2f( lookAt.x * cosf(rotX), lookAt.z );
		float rotZ = atan2f( cosf(rotX), sinf(rotX) * sinf(rotY) );
		pTransform->SetRotationRadians(rotX, -rotY, -rotZ);
		*/

		/*
		//Attempt 4
		Vector3f lookAt = Vector3f::DirectionTo(b, a);	
		float rotX = 0.0f;
		float rotY = atan2f(lookAt.z, lookAt.x);
		float rotZ = atan2f(lookAt.y, sqrtf(lookAt.x*lookAt.x + lookAt.z*lookAt.z));
		pTransform->SetRotationRadians(rotX, rotY, rotZ);
		*/


		//Attempt 5
		/*
		Vector3f lookAt = Vector3f::DirectionTo(b, a);
		float rotX = atan2f(sqrtf(pow(lookAt.x, 2) + pow(lookAt.z, 2)), lookAt.y);
		float rotY = atan2f(lookAt.x, lookAt.z);	
		float rotZ = 0.0f;
		pTransform->SetRotationRadians(rotX, rotY - 1.5707963267948966192313f, rotZ);*/

		//Set the scale
		float distance = Vector3f::Distance(a, b);
		pTransform->SetScale(distance * DISTANCE_SCALE, 0.25f, 0.25f);
	}
}