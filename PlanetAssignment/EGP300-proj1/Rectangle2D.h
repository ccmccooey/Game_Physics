/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  Rectangle2D.h
*
*	Description:
*		This is a simple math class for rectangles in 2D space. This class uses integers to represents the definition of the rectangle.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <ostream>

class Rectangle2D
{
private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;

public:
	Rectangle2D();
	Rectangle2D(int x, int y, int width, int height);
	Rectangle2D(int width, int height);
	Rectangle2D(const Rectangle2D &rhs);
	~Rectangle2D();

	//accessors
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
	double GetDiagnal() const;

	//setters
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);
	void SetRectangle2D(int x, int y, int width, int height);

	//math functions
	int Area() const;
	int Perimeter() const;
	bool ContainsPoint(const Rectangle2D &rectangle2D, float x, float y);
	bool ContainsPoint(const Rectangle2D &rectangle2D, int x, int y);

	//operators overloads
	Rectangle2D& operator = ( const Rectangle2D& rhs );
	bool Rectangle2D::operator==(const Rectangle2D &other) const;
	bool Rectangle2D::operator!=(const Rectangle2D &other) const;

	friend std::ostream& Rectangle2D::operator<<(std::ostream& stream, const Rectangle2D& rectangle);

	//static functions
	static bool Intersection(const Rectangle2D &rectangle1, const Rectangle2D &rectangle2);

	const static Rectangle2D unitRectangle;
};

#endif