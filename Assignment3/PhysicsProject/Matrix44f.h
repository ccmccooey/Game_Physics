#ifndef _MATRIX_44_H
#define _MATRIX_44_H

#include <string>

class Matrix44f
{
private:
	float mData[16];

public:
	const static Matrix44f identity;
	const static Matrix44f zero;	

public:
	Matrix44f();
	Matrix44f(float arrayList[16]);
	Matrix44f(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33);
	Matrix44f(const Matrix44f &rhs);
	~Matrix44f();

	//basic math operator overloads
	Matrix44f& operator = ( const Matrix44f& rhs );
	Matrix44f& operator *= ( const Matrix44f& rhs );
	const Matrix44f operator*(float mult) const;
	const Matrix44f operator*(const Matrix44f& rhs) const;

	//reference operators
	float operator[](int index) const; //get
	float& operator [](int index); //set

	//matrix functions
	Matrix44f Transpose() const;
	float Determinant() const;

	//print operators
	friend std::ostream& Matrix44f::operator<<(std::ostream& stream, const Matrix44f& matrix);
	std::string ToString() const;
	void ToArray(float floatArray[16]);

private:
	//helper functions
	void SwapIndexValuesAt(int a, int b);

};

#endif