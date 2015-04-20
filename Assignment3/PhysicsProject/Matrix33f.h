#ifndef _MATRIX_33_H
#define _MATRIX_33_H

#include <ostream>
#include "Vector3f.h"

class Matrix33f
{
private:
	float mData[9];

public:
	const static Matrix33f identity;
	const static Matrix33f zero;	


public:
	Matrix33f();
	Matrix33f(float arrayList[9]);
	Matrix33f(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);
	Matrix33f(const Matrix33f &rhs);
	~Matrix33f();

	//basic math operator overloads
	Matrix33f& operator = ( const Matrix33f& rhs );
	Matrix33f& operator *= ( const Matrix33f& rhs );
	const Matrix33f operator*(float mult) const;
	const Matrix33f operator*(const Matrix33f& rhs) const;

	//reference operators
	float operator[](int index) const; //get
	float& operator [](int index); //set

	//matrix functions
	Matrix33f Transpose() const;
	float Determinant() const;
	void SetColumns(const Vector3f &first, const Vector3f &second, const Vector3f &third);
	void SetRows(const Vector3f &first, const Vector3f &second, const Vector3f &third);
	Vector3f TransformTranspose(const Vector3f &vector) const;
	void Matrix33f::SetInertiaTensorCoeffs(float ix, float iy, float iz, float ixy = 0.0f, float ixz = 0.0f, float iyz = 0.0f);
	void SetBlockInertiaTensor(const Vector3f &halfSizes, float mass);

	//static functions
	static Matrix33f Matrix33f::Lerp(const Matrix33f& a, const Matrix33f& b, float lerpValue);
	
	//print operators
	friend std::ostream& Matrix33f::operator<<(std::ostream& stream, const Matrix33f& matrix);
	std::string ToString() const;
	void ToArray(float floatArray[9]);

private:
	//helper functions
	void SwapIndexValuesAt(int a, int b);

};

#endif