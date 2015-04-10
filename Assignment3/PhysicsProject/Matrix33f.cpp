#include "Matrix33f.h"

Matrix33f::Matrix33f()
{
	m3dLoadIdentity33(mat);

	mData[0] = 1.0f; mData[1] = 0.0f; mData[2] = 0.0f;
	mData[3] = 0.0f; mData[4] = 1.0f; mData[5] = 0.0f;
	mData[6] = 0.0f; mData[7] = 0.0f; mData[8] = 1.0f;
}
Matrix33f::~Matrix33f()
{

}

/*
Matrix33f& Matrix33f::operator = ( const Matrix33f& rhs )
{
	mData[0] = rhs.mData[0]; mData[1] = rhs.mData[1]; mData[2] = rhs.mData[2]; 
	mData[3] = rhs.mData[3]; mData[4] = rhs.mData[4]; mData[5] = rhs.mData[5];
	mData[6] = rhs.mData[6]; mData[7] = rhs.mData[7]; mData[8] = rhs.mData[8];
}

Matrix33f& Matrix33f::operator *= ( const Matrix33f& rhs )
{
	
}

const Matrix33f Matrix33f::operator*(float mult) const
{

}

std::ostream& operator<<(std::ostream& stream, const Matrix33f& matrix)
{

}
std::string Matrix33f::ToString() const
{

}*/
void Matrix33f::ToArray(float floatArray[9])
{
	floatArray[0] = mData[0]; floatArray[1] = mData[1]; floatArray[2] = mData[2];
	floatArray[3] = mData[3]; floatArray[4] = mData[4]; floatArray[5] = mData[5];
	floatArray[6] = mData[6]; floatArray[7] = mData[7]; floatArray[8] = mData[8];
}