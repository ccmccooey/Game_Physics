/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  Rectangle2D.cpp
*
*	Description:
*		This is a simple math class for rectangles in 2D space. This class uses integers to represents the definition of the rectangle.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/
#include "Rectangle2D.h"
#include <math.h>

//unit rectangle
const Rectangle2D Rectangle2D::unitRectangle = Rectangle2D(0, 0, 1, 1);

using namespace std;

//constructors
Rectangle2D::Rectangle2D()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
}
Rectangle2D::Rectangle2D(int x, int y, int width, int height)
{
	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;
}
Rectangle2D::Rectangle2D(int width, int height)
{
	mX = 0;
	mY = 0;
	mWidth = width;
	mHeight = height;
}
Rectangle2D::Rectangle2D(const Rectangle2D &rhs)
{
	mX = rhs.mX;
	mY = rhs.mY;
	mWidth = rhs.mWidth;
	mHeight = rhs.mHeight;
}
Rectangle2D::~Rectangle2D()
{

}

//accessors
int Rectangle2D::GetX() const
{
	return mX;
}
int Rectangle2D::GetY() const
{
	return mY;
}
int Rectangle2D::GetWidth() const
{
	return mWidth;
}
int Rectangle2D::GetHeight() const	
{
	return mHeight;
}
double Rectangle2D::GetDiagnal() const
{
	return sqrt((mWidth * mWidth) + (mHeight * mHeight));
}

//setters
void Rectangle2D::SetX(int x)
{
	mX = x;
}
void Rectangle2D::SetY(int y)
{
	mY = y;
}
void Rectangle2D::SetWidth(int width)
{
	mWidth = width;
}
void Rectangle2D::SetHeight(int height)
{
	mHeight = height;
}
void Rectangle2D::SetPosition(int x, int y)
{
	mX = x;
	mY = y;
}
void Rectangle2D::SetSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}
void Rectangle2D::SetRectangle2D(int x, int y, int width, int height)
{
	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;
}

//math functions
int Rectangle2D::Area() const
{
	return mWidth * mHeight;
}
int Rectangle2D::Perimeter() const
{
	return mWidth + mWidth + mHeight + mHeight;
}
bool Rectangle2D::ContainsPoint(const Rectangle2D &rectangle, float x, float y)
{
	return ContainsPoint(rectangle, (int)x, (int) y);
}
bool Rectangle2D::ContainsPoint(const Rectangle2D &rectangle, int x, int y)
{
	return (x >= rectangle.mX && x <= rectangle.mWidth && y >= rectangle.mY && y <= rectangle.mHeight);
}

//operators overloads
Rectangle2D& Rectangle2D::operator = ( const Rectangle2D& rhs )
{
	mX = rhs.mX;
	mY = rhs.mY;
	mWidth = rhs.mWidth;
	mHeight = rhs.mHeight;
	return (*this);
}
bool Rectangle2D::operator==(const Rectangle2D &other) const
{
	return (mX == other.mX && mY == other.mY && mWidth == other.mWidth && mHeight == other.mHeight);
}
bool Rectangle2D::operator!=(const Rectangle2D &other) const
{
	return (mX != other.mX || mY != other.mY || mWidth != other.mWidth || mHeight != other.mHeight);
}
std::ostream& operator<<(std::ostream& stream, const Rectangle2D& rectangle)
{
	stream << "(" << rectangle.mX << ", " << rectangle.mY << ", " << rectangle.mWidth << ", " << rectangle.mHeight << ")";
	return stream;
}

//static functions
bool Rectangle2D::Intersection(const Rectangle2D &rectangle1, const Rectangle2D &rectangle2)
{
	return false;
}