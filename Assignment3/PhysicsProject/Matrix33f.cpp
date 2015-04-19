#include "Matrix33f.h"
#include <sstream>

const Matrix33f Matrix33f::identity = Matrix33f(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
const Matrix33f Matrix33f::zero = Matrix33f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

Matrix33f::Matrix33f()
{
	//m3dLoadIdentity33(mat);

	mData[0] = 1.0f; mData[1] = 0.0f; mData[2] = 0.0f;
	mData[3] = 0.0f; mData[4] = 1.0f; mData[5] = 0.0f;
	mData[6] = 0.0f; mData[7] = 0.0f; mData[8] = 1.0f;
}
Matrix33f::Matrix33f(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
	mData[0] = v00; mData[1] = v01; mData[2] = v02;
	mData[3] = v10; mData[4] = v11; mData[5] = v12;
	mData[6] = v20; mData[7] = v21; mData[8] = v22;
}
Matrix33f::Matrix33f(const Matrix33f &rhs)
{
	*this = rhs;
}

Matrix33f::~Matrix33f()
{

}


Matrix33f& Matrix33f::operator = ( const Matrix33f& rhs )
{
	mData[0] = rhs.mData[0]; mData[1] = rhs.mData[1]; mData[2] = rhs.mData[2]; 
	mData[3] = rhs.mData[3]; mData[4] = rhs.mData[4]; mData[5] = rhs.mData[5];
	mData[6] = rhs.mData[6]; mData[7] = rhs.mData[7]; mData[8] = rhs.mData[8];
	return *this;
}

Matrix33f& Matrix33f::operator *= ( const Matrix33f& rhs )
{
	return *this;
}

const Matrix33f Matrix33f::operator*(float mult) const
{
	Matrix33f mat = Matrix33f();
	mat.mData[0] *= mult; mat.mData[1] *= mult; mat.mData[2] *= mult;
	mat.mData[3] *= mult; mat.mData[4] *= mult; mat.mData[5] *= mult;
	mat.mData[6] *= mult; mat.mData[7] *= mult; mat.mData[8] *= mult;
	return mat;
}
const Matrix33f Matrix33f::operator*(const Matrix33f& rhs) const
{
	/*
	a11xb11 + a12xb21 + a13xb31,	a11xb12 + a12xb22 + a13xb32,	a11xb13 + a12xb23 + a13xb33
	a21xb11 + a22xb21 + a23xb31,	a21xb12 + a22xb22 + a23xb32,	a21xb13 + a22xb23 + a23xb33
	a31xb11 + a32xb21 + a33xb31,	a31xb12 + a32xb22 + a33xb32,	a31xb13 + a32xb23 + a33xb33
	*/

	return Matrix33f
		(
		mData[0] * rhs.mData[0] + mData[1] * rhs.mData[3] + mData[2] * rhs.mData[6],
		mData[0] * rhs.mData[1] + mData[1] * rhs.mData[4] + mData[2] * rhs.mData[7],
		mData[0] * rhs.mData[2] + mData[1] * rhs.mData[5] + mData[2] * rhs.mData[8],
		mData[3] * rhs.mData[0] + mData[4] * rhs.mData[3] + mData[5] * rhs.mData[6],
		mData[3] * rhs.mData[1] + mData[4] * rhs.mData[4] + mData[5] * rhs.mData[7],
		mData[3] * rhs.mData[2] + mData[4] * rhs.mData[5] + mData[5] * rhs.mData[8],
		mData[6] * rhs.mData[0] + mData[7] * rhs.mData[3] + mData[8] * rhs.mData[6],
		mData[6] * rhs.mData[1] + mData[7] * rhs.mData[4] + mData[8] * rhs.mData[7],
		mData[6] * rhs.mData[2] + mData[7] * rhs.mData[5] + mData[8] * rhs.mData[8]
	);
		

}

//reference operators
float Matrix33f::operator[](int index) const
{
	return mData[index];
}
float& Matrix33f::operator[](int index)
{
	return mData[index];
}

//matrix functions
Matrix33f Matrix33f::Transpose() const
{
	return Matrix33f(mData[0], mData[3], mData[6], mData[1], mData[4], mData[7], mData[2], mData[5], mData[8]);
}
float Matrix33f::Determinant() const
{
	return 
		(mData[0] * mData[4] * mData[8]) + (mData[1] * mData[5] * mData[6]) + (mData[2] * mData[3] * mData[7]) -
		(mData[6] * mData[4] * mData[2]) - (mData[7] * mData[5] * mData[0]) - (mData[8] * mData[3] * mData[1]); 
}

//helper functions
void Matrix33f::SwapIndexValuesAt(int a, int b)
{
	float tmp = mData[a];
	mData[a] = mData[b];
	mData[b] = tmp;
}

//stream operators
std::ostream& operator<<(std::ostream& stream, const Matrix33f& matrix)
{
	stream << "[" 
		<< matrix.mData[0] << ", " << matrix.mData[1] << ", " << matrix.mData[2] << "; "
		<< matrix.mData[3] << ", " << matrix.mData[4] << ", " << matrix.mData[5] << "; "
		<< matrix.mData[6] << ", " << matrix.mData[7] << ", " << matrix.mData[8] << 
		"]";

	return stream;
}
std::string Matrix33f::ToString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Matrix33f::ToArray(float floatArray[9])
{
	floatArray[0] = mData[0]; floatArray[1] = mData[1]; floatArray[2] = mData[2];
	floatArray[3] = mData[3]; floatArray[4] = mData[4]; floatArray[5] = mData[5];
	floatArray[6] = mData[6]; floatArray[7] = mData[7]; floatArray[8] = mData[8];
}