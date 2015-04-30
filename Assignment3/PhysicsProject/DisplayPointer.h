#ifndef _DISPLAY_POINTER_H
#define _DISPLAY_POINTER_H

class DisplayObject3D;
class GameObject;

class DisplayPointer
{
private:
	GameObject* mObject; //this represents the gameobject the object is latched to
	DisplayObject3D* mDisplay;

public:
	DisplayPointer();
	~DisplayPointer();

	bool IsLatched() const;

	void LatchTo(GameObject *object);
	void UnLatch();

	void Update();
};

#endif