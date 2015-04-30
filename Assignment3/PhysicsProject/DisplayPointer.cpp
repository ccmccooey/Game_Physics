#include "DisplayPointer.h"
#include "GameObject.h"
#include "GraphicsSystem.h"
#include "DisplayObject3D.h"
#include "Model.h"
#include "Material.h"

DisplayPointer::DisplayPointer()
{
	mObject = nullptr;
}
DisplayPointer::~DisplayPointer()
{
	UnLatch();
}

bool DisplayPointer::IsLatched() const
{
	return mObject != nullptr;
}

void DisplayPointer::LatchTo(GameObject *object)
{
	if (object == nullptr)
	{
		UnLatch();
	}
	
	if (mObject == nullptr)
	{
		mDisplay = new DisplayObject3D(GraphicsSystem::GetModel("Quad"));
		mDisplay->SetMaterial(GraphicsSystem::GetMaterial("DisplayPointer"));

		GraphicsSystem::AddDisplayObject(mDisplay);
	}
	mObject = object;
}
void DisplayPointer::UnLatch()
{
	if (mObject != nullptr)
	{
		GraphicsSystem::RemoveDisplayObject(mDisplay);
		mObject = nullptr;
	}
}

void DisplayPointer::UpdatePosition()
{
	if (mObject != nullptr)
	{
		Transform* t = mObject->GetGraphicsObject()->getTransform();
		mDisplay->getTransform()->SetPosition(t->GetPosition() + (Vector3f::unitY * t->GetScale().y));
	}
}