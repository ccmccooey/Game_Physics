#ifndef _CAMERA_CONTAINER_H
#define _CAMERA_CONTAINER_H

#include "Vector3f.h"

class DisplayObject3D;
class Camera;

class CameraContainer
{
private:
	Camera* mCamera;
	DisplayObject3D* mLatchedObject;
	Vector3f mPosition;

public:
	CameraContainer(Camera* camera);
	~CameraContainer();

	Camera* GetCamera() const;
	DisplayObject3D* GetLatchedObject() const;
	bool IsLatched() const;

	void Latch(DisplayObject3D* obj);
	void UnLatch();
	void Update();

	void SetPosition(const Vector3f &position);
	void SetPosition(float x, float y, float z);
	void Translate(const Vector3f &position);
	void Translate(float x, float y, float z);

private:
	void UpdatePosition();

};

#endif