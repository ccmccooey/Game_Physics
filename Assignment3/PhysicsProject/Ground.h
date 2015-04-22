#ifndef _GROUND_H
#define _GROUND_H

class DisplayObject3D;

class Ground
{
private:
	DisplayObject3D* mDisplayObject;
	float mElevation;

public:
	Ground();
	~Ground();
};

#endif