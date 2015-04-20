#include "Matrix44f.h"

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
	return 
		(mData[0] * mData[4] * mData[8]) + (mData[1] * mData[5] * mData[6]) + (mData[2] * mData[3] * mData[7]) -
		(mData[6] * mData[4] * mData[2]) - (mData[7] * mData[5] * mData[0]) - (mData[8] * mData[3] * mData[1]); */
}