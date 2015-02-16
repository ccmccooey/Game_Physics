#include "CameraContainer.h"
#include "Camera.h"
#include "DisplayObject3D.h"

//constructor
CameraContainer::CameraContainer(Camera* camera)
{
	mCamera = camera;
	mLatchedObject = nullptr;
	mPosition = camera->getPosition();
	UpdatePosition();
}
CameraContainer::~CameraContainer()
{

}

//accessors
Camera* CameraContainer::GetCamera() const
{
	return mCamera;
}
DisplayObject3D* CameraContainer::GetLatchedObject() const
{
	return mLatchedObject;
}
bool CameraContainer::IsLatched() const
{
	return mLatchedObject != nullptr;
}

//latching
void CameraContainer::Latch(DisplayObject3D* obj)
{
	if (obj != nullptr)
	{
		mLatchedObject = obj;
		mPosition = Vector3f(0.0f, 0.0f, 30.0f);
		mCamera->resetRotation();
		UpdatePosition();
	}
}
void CameraContainer::UnLatch()
{
	mLatchedObject = nullptr;
	//mPosition = Vector3f(0.0f, 0.0f, 0.0f);
	mCamera->resetRotation();
	mPosition = Vector3f(0.0f, 5.0f, 30.0f);
	UpdatePosition();
}
void CameraContainer::Update()
{
	UpdatePosition();
}

//setters
void CameraContainer::SetPosition(const Vector3f &position)
{
	mPosition = position;
	UpdatePosition();
}
void CameraContainer::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	UpdatePosition();
}
void CameraContainer::Translate(const Vector3f &position)
{
	mPosition += position;
	UpdatePosition();
}
void CameraContainer::Translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
	UpdatePosition();
}


void CameraContainer::UpdatePosition()
{
	if (mLatchedObject != nullptr)
	{
		mCamera->setPosition(mLatchedObject->getTransform()->GetPosition() + mPosition);
	}
	else
	{
		mCamera->setPosition(mPosition);
	}
}