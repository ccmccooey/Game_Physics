#include "PointLight.h"
#include "Color.h"

//constructor
PointLight::PointLight(float x, float y, float z)
{
	mPositionData = new GLfloat[4];
	mPositionData[0] = x;
	mPositionData[1] = y;
	mPositionData[2] = z;
	mPositionData[3] = 0.0f;
	//mX = x;
	//mY = y;
	//mZ = z;
	mColor = Color(0.25f, 0.25f, 0.25f, 1.0f);
	mColorData = new float[4];
	glEnable(GL_LIGHT1);
	calculate();
}

//destructor
PointLight::~PointLight()
{
	delete [] mColorData;
	delete [] mPositionData;
}


//setters
void PointLight::setColor(const Color& color)
{
	mColor = color;
	calculate();
}
void PointLight::setColor(float r, float g, float b, float a)
{
	mColor.Set(r, g, b, a);
	calculate();
}
void PointLight::setPosition(float x, float y, float z)
{
	//mX = x;
	//mY = y;
	//mZ = z;
	mPositionData[0] = x;
	mPositionData[1] = y;
	mPositionData[2] = z;
	calculate();
}

//open GL stuff
void PointLight::calculate()
{
	mColorData[0] = mColor.R();
	mColorData[1] = mColor.G();
	mColorData[2] = mColor.B();
	mColorData[3] = mColor.A();
	glLightfv(GL_LIGHT0, GL_POSITION, mPositionData);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mColorData);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mColorData);
	//glLightModelfv(
}