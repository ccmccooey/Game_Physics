/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 15, 2015
*	Filename:  Color.cpp
*
*	Description:
*		This class is a simple rgba data structure for colors. It uses float values between 0 and 1. The class contains some predefined colors.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Color.h"

const Color Color::Red = Color(1, 0, 0, 1);
const Color Color::Green = Color(0, 1, 0, 1);
const Color Color::Blue = Color(0, 0, 1, 1);
const Color Color::Black = Color(0, 0, 0, 1);
const Color Color::White = Color(1, 1, 1, 1);
const Color Color::Yellow = Color(1, 1, 0, 1);
const Color Color::Cyan = Color(0, 1, 1, 1);
const Color Color::Magenta = Color(1, 0, 1, 1);

Color::Color()
{
	Set(0.0, 0.0, 0.0, 1.0);
}
Color::Color(float r, float g, float b, float a)
{
	Set(r, g, b, a);
}
Color::Color(const Color& rhs)
{
	Set(rhs.R(), rhs.G(), rhs.B(), rhs.A());
}
Color::~Color()
{

}

float Color::R() const
{
	return mRGBA[0];
}
float Color::G() const
{
	return mRGBA[1];
}
float Color::B() const
{
	return mRGBA[2];
}
float Color::A() const
{
	return mRGBA[3];
}

void Color::Set(float r, float g, float b, float a)
{
	mRGBA[0] = r;
	mRGBA[1] = g;
	mRGBA[2] = b;
	mRGBA[3] = a;
}
void Color::ToColorArrayRGBA(GLfloat* &colorArray)
{
	colorArray = mRGBA;
}
void Color::ToFloatArray4(const float arr[4]) const
{
	arr = mRGBA;
}

//assignment operator
Color& Color::operator=( const Color& rhs )
{
	mRGBA[0] = rhs.mRGBA[0];
	mRGBA[1] = rhs.mRGBA[1];
	mRGBA[2] = rhs.mRGBA[2];
	mRGBA[3] = rhs.mRGBA[3];
	return *this;
}

//equalivilent operators
bool Color::operator==(const Color &other) const
{
	return (mRGBA[0] == other.mRGBA[0] && mRGBA[1] == other.mRGBA[1] && mRGBA[2] == other.mRGBA[2] && mRGBA[3] == other.mRGBA[3]);
}
bool Color::operator!=(const Color &other) const
{
	return (mRGBA[0] != other.mRGBA[0] || mRGBA[1] != other.mRGBA[1] || mRGBA[2] != other.mRGBA[2] || mRGBA[3] != other.mRGBA[3]);
}