#include "Matrix44f.h"
#include <sstream>

//constant matricies
const Matrix44f Matrix44f::identity = Matrix44f(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
const Matrix44f Matrix44f::zero = Matrix44f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

//constructors
Matrix44f::Matrix44f()
{
	mData[0] = 1.0f; mData[1] = 0.0f; mData[2] = 0.0f; mData[3] = 0.0f;
	mData[4] = 0.0f; mData[5] = 1.0f; mData[6] = 0.0f; mData[7] = 0.0f;
	mData[8] = 0.0f; mData[9] = 0.0f; mData[10] = 1.0f; mData[11] = 0.0f;
	mData[12] = 0.0f; mData[13] = 0.0f; mData[14] = 0.0f; mData[15] = 1.0f;
}
Matrix44f::Matrix44f(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
{
	mData[0] = v00; mData[1] = v01; mData[2] = v02; mData[3] = v03;
	mData[4] = v10; mData[5] = v11; mData[6] = v12; mData[7] = v13;
	mData[8] = v20; mData[9] = v21; mData[10] = v22; mData[11] = v23;
	mData[12] = v30; mData[13] = v31; mData[14] = v32; mData[15] = v33;
}
Matrix44f::Matrix44f(const Matrix44f &rhs)
{
	*this = rhs;
}
Matrix44f::~Matrix44f()
{

}

//operators
Matrix44f& Matrix44f::operator = ( const Matrix44f& rhs )
{
	mData[0] = rhs.mData[0]; mData[1] = rhs.mData[1]; mData[2] = rhs.mData[2]; mData[3] = rhs.mData[3];
	mData[4] = rhs.mData[4]; mData[5] = rhs.mData[5]; mData[6] = rhs.mData[6]; mData[7] = rhs.mData[7];
	mData[8] = rhs.mData[8]; mData[9] = rhs.mData[9]; mData[10] = rhs.mData[10]; mData[11] = rhs.mData[11];
	mData[12] = rhs.mData[12]; mData[13] = rhs.mData[13]; mData[14] = rhs.mData[14]; mData[15] = rhs.mData[15];
	return *this;
}
const Matrix44f Matrix44f::operator*(float mult) const
{
	return Matrix44f(mData[0] * mult, mData[1] * mult, mData[2] * mult, mData[3] * mult,
				     mData[4] * mult, mData[5] * mult, mData[6] * mult, mData[7] * mult,
					 mData[8] * mult, mData[9] * mult, mData[10] * mult, mData[11] * mult,
					 mData[12] * mult, mData[13] * mult, mData[14] * mult, mData[15] * mult);
}
const Matrix44f Matrix44f::operator*(const Matrix44f& rhs) const
{
	return Matrix44f //A lot of calculations
		(
		mData[0] * rhs.mData[0] + mData[1] * rhs.mData[4] + mData[2] * rhs.mData[8] + mData[3] * rhs.mData[12],
		mData[0] * rhs.mData[1] + mData[1] * rhs.mData[5] + mData[2] * rhs.mData[9] + mData[3] * rhs.mData[13],
		mData[0] * rhs.mData[2] + mData[1] * rhs.mData[6] + mData[2] * rhs.mData[10] + mData[3] * rhs.mData[14],
		mData[0] * rhs.mData[3] + mData[1] * rhs.mData[7] + mData[2] * rhs.mData[11] + mData[3] * rhs.mData[15],
		mData[4] * rhs.mData[0] + mData[5] * rhs.mData[4] + mData[6] * rhs.mData[8] + mData[7] * rhs.mData[12],
		mData[4] * rhs.mData[1] + mData[5] * rhs.mData[5] + mData[6] * rhs.mData[9] + mData[7] * rhs.mData[13],
		mData[4] * rhs.mData[2] + mData[5] * rhs.mData[6] + mData[6] * rhs.mData[10] + mData[7] * rhs.mData[14],
		mData[4] * rhs.mData[3] + mData[5] * rhs.mData[7] + mData[6] * rhs.mData[11] + mData[7] * rhs.mData[15],
		mData[8] * rhs.mData[0] + mData[9] * rhs.mData[4] + mData[10] * rhs.mData[8] + mData[11] * rhs.mData[12],
		mData[8] * rhs.mData[1] + mData[9] * rhs.mData[5] + mData[10] * rhs.mData[9] + mData[11] * rhs.mData[13],
		mData[8] * rhs.mData[2] + mData[9] * rhs.mData[6] + mData[10] * rhs.mData[10] + mData[11] * rhs.mData[14],
		mData[8] * rhs.mData[3] + mData[9] * rhs.mData[7] + mData[10] * rhs.mData[11] + mData[11] * rhs.mData[15],
		mData[12] * rhs.mData[0] + mData[13] * rhs.mData[4] + mData[14] * rhs.mData[8] + mData[15] * rhs.mData[12],
		mData[12] * rhs.mData[1] + mData[13] * rhs.mData[5] + mData[14] * rhs.mData[9] + mData[15] * rhs.mData[13],
		mData[12] * rhs.mData[2] + mData[13] * rhs.mData[6] + mData[14] * rhs.mData[10] + mData[15] * rhs.mData[14],
		mData[12] * rhs.mData[3] + mData[13] * rhs.mData[7] + mData[14] * rhs.mData[11] + mData[15] * rhs.mData[15]		
	);
}

//reference operators
float Matrix44f::operator[](int index) const
{
	return mData[index];
}
float& Matrix44f::operator[](int index)
{
	return mData[index];
}

//matrix functions
Matrix44f Matrix44f::Transpose() const
{
	return Matrix44f(mData[0], mData[4], mData[8], mData[12], mData[1], mData[5], mData[9], mData[13], mData[2], mData[6], mData[10], mData[14], mData[3], mData[7], mData[11], mData[15]);
}
float Matrix44f::Determinant() const
{	
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15
	*/
	return mData[0] * Matrix44f::Determinant33(5, 6, 7, 9, 10, 11, 13, 14, 15) -
		   mData[1] * Matrix44f::Determinant33(4, 6, 7, 8, 10, 11, 12, 14, 15) +
		   mData[2] * Matrix44f::Determinant33(4, 5, 7, 8, 9, 11, 12, 13, 15) -
		   mData[3] * Matrix44f::Determinant33(4, 5, 6, 8, 9, 10, 12, 13, 14);
}
float Matrix44f::Determinant33(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22)  const
{
	/*
	00 01 02
	10 11 12
	20 21 22
	*/

	return 
		(mData[v00] * mData[v11] * mData[v22]) + (mData[v01] * mData[v12] * mData[v20]) + (mData[v02] * mData[v10] * mData[v21]) -
		(mData[v20] * mData[v11] * mData[v02]) - (mData[v21] * mData[v12] * mData[v00]) - (mData[v22] * mData[v10] * mData[v01]); 
}

//helper functions
void Matrix44f::SwapIndexValuesAt(int a, int b)
{
	float tmp = mData[a];
	mData[a] = mData[b];
	mData[b] = tmp;
}

//stream operators
std::ostream& operator<<(std::ostream& stream, const Matrix44f& matrix)
{
	stream << "[" 
		<< matrix.mData[0] << ", " << matrix.mData[1] << ", " << matrix.mData[2] << ", " << matrix.mData[3] << "; "
		<< matrix.mData[4] << ", " << matrix.mData[5] << ", " << matrix.mData[6] << ", " << matrix.mData[7] << "; "
		<< matrix.mData[8] << ", " << matrix.mData[9] << ", " << matrix.mData[10] << ", " << matrix.mData[11] << "; "
		<< matrix.mData[12] << ", " << matrix.mData[13] << ", " << matrix.mData[14] << ", " << matrix.mData[15] <<
		"]";

	return stream;
}
std::string Matrix44f::ToString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Matrix44f::ToArray(float floatArray[16])
{
	floatArray[0] = mData[0]; floatArray[1] = mData[1]; floatArray[2] = mData[2]; floatArray[3] = mData[3];
	floatArray[4] = mData[4]; floatArray[5] = mData[5]; floatArray[6] = mData[6]; floatArray[7] = mData[7];
	floatArray[8] = mData[8]; floatArray[9] = mData[9]; floatArray[10] = mData[10]; floatArray[11] = mData[11];
	floatArray[12] = mData[12]; floatArray[13] = mData[13]; floatArray[14] = mData[14]; floatArray[15] = mData[15];
}

//special matricies to generate
void Matrix44f::CreateTranslationMatrix(Matrix44f &result, const Vector3f &translation)
{
	result.mData[0] = 1.0f; result.mData[1] = 0.0f; result.mData[2] = 0.0f; result.mData[3] = translation.x;
	result.mData[4] = 0.0f; result.mData[5] = 1.0f; result.mData[6] = 0.0f; result.mData[7] = translation.y;
	result.mData[8] = 0.0f; result.mData[9] = 0.0f; result.mData[10] = 1.0f; result.mData[11] = translation.z;
	result.mData[12] = 0.0f; result.mData[13] = 0.0f; result.mData[14] = 0.0f; result.mData[15] = 1.0f;
}
void Matrix44f::CreateScaleMatrix(Matrix44f &result, const Vector3f &scale)
{
	result.mData[0] = scale.x; result.mData[1] = 0.0f; result.mData[2] = 0.0f; result.mData[3] = 0.0f;
	result.mData[4] = 0.0f; result.mData[5] = scale.y; result.mData[6] = 0.0f; result.mData[7] = 0.0f;
	result.mData[8] = 0.0f; result.mData[9] = 0.0f; result.mData[10] = scale.z; result.mData[11] = 0.0f;
	result.mData[12] = 0.0f; result.mData[13] = 0.0f; result.mData[14] = 0.0f; result.mData[15] = 1.0f;
}
void Matrix44f::CreateRotationMatrix(Matrix44f &result, const Vector3f &anglesRadians)
{
	result.mData[0] = cosf(anglesRadians.y) * cosf(anglesRadians.z); result.mData[1] = -sinf(anglesRadians.z); result.mData[2] = sinf(anglesRadians.z); result.mData[3] = 0.0f;
	result.mData[4] = sinf(anglesRadians.z); result.mData[5] = cosf(anglesRadians.x) * cosf(anglesRadians.z); result.mData[6] = -sinf(anglesRadians.x); result.mData[7] = 0.0f;
	result.mData[8] = -sinf(anglesRadians.y); result.mData[9] = sinf(anglesRadians.x); result.mData[10] = cosf(anglesRadians.x) * cosf(anglesRadians.y); result.mData[11] = 0.0f;
	result.mData[12] = 0.0f; result.mData[13] = 0.0f; result.mData[14] = 0.0f; result.mData[15] = 1.0f;
}
void Matrix44f::CreateRTSMatrix(Matrix44f &result, const Vector3f &translation, const Vector3f &anglesRadians, const Vector3f &scale)
{
	Matrix44f rotationMatrix, translationMatrix, scaleMatrix;
	Matrix44f::CreateRotationMatrix(rotationMatrix, anglesRadians);
	Matrix44f::CreateTranslationMatrix(translationMatrix, translation);
	Matrix44f::CreateScaleMatrix(scaleMatrix, scale);

	result = ((rotationMatrix * translationMatrix) * scaleMatrix);
}