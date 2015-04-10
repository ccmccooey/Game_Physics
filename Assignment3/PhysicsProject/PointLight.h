#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H

#include "GLfiles.h"
#include "Color.h"

class PointLight
{
public:
	PointLight(float xPosition, float yPosition, float zPosition);
	~PointLight();

	void setColor(const Color &color);
	void setColor(float r, float g, float b, float a);
	void setPosition(float x, float y, float z);

	GLfloat* getPositionData(){return mPositionData;};
	GLfloat* getColorData(){return mColorData;};
private:
	void calculate();

private:
	//float mX, mY, mZ;
	GLfloat* mPositionData;
	Color mColor;
	GLfloat* mColorData;
};

#endif