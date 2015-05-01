#include "Ground.h"
#include "MainApp.h"
#include "GraphicsSystem.h"
#include "DisplayObject3D.h"
#include "PhysicsSystem.h"
#include "CollisionPlane.h"

Ground::Ground()
{	
	mElevation = -30.0f;
	mDisplayObject = new DisplayObject3D(GraphicsSystem::GetModel("Quad"));
	mDisplayObject->SetMaterial(GraphicsSystem::GetMaterial("DirtTerrain"));
	mCollisionPlane = new CollisionPlane(Vector3f::unitY, mElevation, false);
	MainApp::GetPhysicsSystem()->AddNewCollider(static_cast<CollisionPrimitive*>(mCollisionPlane));

	float scale = 500.0f;
	Transform* transform = mDisplayObject->getTransform();
	//transform->SetPosition(-scale * 0.5f, mElevation, scale * 0.5f);
	transform->SetPosition(0.0f, mElevation, 0.0f);
	transform->SetRotationDegrees(90.0f, 0.0f, 0.0f);
	transform->SetScale(scale, scale, scale);
	GraphicsSystem::AddDisplayObject(mDisplayObject);
}
Ground::~Ground()
{
	GraphicsSystem::RemoveDisplayObject(mDisplayObject);
}

void Ground::SetMaterial(const std::string &name)
{
	mDisplayObject->SetMaterial(GraphicsSystem::GetMaterial(name));
}