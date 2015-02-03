/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 15, 2015
*	Filename:  Color.h
*
*	Description:
*		This class is a simple rgba data structure for colors. It uses float values between 0 and 1. The class contains some predefined colors.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _COLOR_H
#define _COLOR_H

#include "GLfiles.h"

class Color
{
public:
	Color();
	Color(float r, float g, float b, float a);
	Color(const Color &rhs);
	~Color();
	void Set(float r, float g, float b, float a);
	void ToColorArrayRGBA(GLfloat* &colorArray);

	float R() const;
	float G() const;
	float B() const;
	float A() const;

	//operators
	Color& operator = ( const Color& rhs );
	bool operator==(const Color &other) const;
	bool operator!=(const Color &other) const;

private:
	float mRGBA[4];

public:
	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color Black;
	const static Color White;
	const static Color Yellow;
	const static Color Cyan;
	const static Color Magenta;
	
};

#endif