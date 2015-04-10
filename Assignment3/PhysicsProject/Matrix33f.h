#ifndef _MATRIX_33_H
#define _MATRIX_33_H

#include <ostream>
#include "GLfiles.h"

class Matrix33f
{
private:
	float mData[9];

public:
	M3DMatrix33f mat; //temporary
	

	const static M3DMatrix44f identity;
	const static M3DMatrix44f zero;
	const static M3DMatrix44f one;


public:
	Matrix33f();
	Matrix33f(float arrayList[9]);
	Matrix33f(const M3DMatrix44f &rhs);
	~Matrix33f();

	Matrix33f& operator = ( const Matrix33f& rhs );
	Matrix33f& operator *= ( const Matrix33f& rhs );
	const Matrix33f Matrix33f::operator*(float mult) const;

	friend std::ostream& Matrix33f::operator<<(std::ostream& stream, const Matrix33f& matrix);
	std::string ToString() const;
	void ToArray(float floatArray[9]);

};

#endif