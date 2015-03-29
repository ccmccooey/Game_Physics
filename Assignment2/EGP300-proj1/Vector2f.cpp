#include "Vector2f.h"
#include <sstream>
#include <math.h>
#include <string.h>

//static vectors
const Vector2f Vector2f::zero = Vector2f(0.0f, 0.0f);
const Vector2f Vector2f::one = Vector2f(1.0f, 1.0f);
const Vector2f Vector2f::unitX = Vector2f(1.0f, 0.0f);
const Vector2f Vector2f::unitY = Vector2f(0.0f, 1.0f);

//constructors
Vector2f::Vector2f()
{
	x = 0.0f;
	y = 0.0f;
}
Vector2f::Vector2f(float X)
{
	x = X;
	y = 0.0f;
}
Vector2f::Vector2f(float X, float Y)
{
	x = X;
	y = Y;
}
Vector2f::Vector2f(const Vector2f &rhs)
{
	x = rhs.x;
	y = rhs.y;
}
Vector2f::Vector2f(const Vector2f *rhs)
{
	x = rhs->x;
	y = rhs->y;
}
Vector2f::Vector2f(const float xy[])
{
	x = xy[0];
	y = xy[1];
}

//destructor
Vector2f::~Vector2f()
{
}

//setters
void Vector2f::Set(float X, float Y)
{
	x = X;
	y = Y;
}

//assignment operator
Vector2f& Vector2f::operator=( const Vector2f& rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

//relative operators
Vector2f& Vector2f::operator += ( const Vector2f& rhs )
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}
Vector2f& Vector2f::operator -= ( const Vector2f& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
Vector2f& Vector2f::operator *= ( const Vector2f& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}
Vector2f& Vector2f::operator /= ( const Vector2f& rhs )
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}
Vector2f& Vector2f::operator *= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	return *this;
}
Vector2f& Vector2f::operator /= ( float scalar )
{
	x /= scalar;
	y /= scalar;
	return *this;
}

//math operators
const Vector2f Vector2f::operator+(const Vector2f &other) const
{
	return Vector2f(x + other.x, y + other.y);
}
const Vector2f Vector2f::operator-(const Vector2f &other) const
{
	return Vector2f(x - other.x, y - other.y);
}
const Vector2f Vector2f::operator*(const Vector2f &other) const
{
	return Vector2f(x * other.x, y * other.y);
}
const Vector2f Vector2f::operator/(const Vector2f &other) const
{
	return Vector2f(x / other.x, y / other.y);
}
const Vector2f Vector2f::operator-() const
{
	return Vector2f(x * -1, y * -1);
}
const Vector2f Vector2f::operator*(float mult) const
{
	return Vector2f(x * mult, y * mult);
}
const Vector2f Vector2f::operator/(float div) const
{
	return Vector2f(x / div, y / div);
}

//comparison operators
bool Vector2f::operator==(const Vector2f& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}
bool Vector2f::operator!=(const Vector2f& rhs) const
{
	return (x != rhs.x && y != rhs.y);
}

//streaming operators
std::ostream& operator<<(std::ostream& stream, const Vector2f& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}

//to string
std::string Vector2f::toString()
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Vector2f::toArray(float floatArray[2])
{
	floatArray[0] = x;
	floatArray[1] = y;
}


//math functions
void Vector2f::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
}
void Vector2f::lengthinize(float value)
{
	float length = this->length();
	x /= length * value;
	y /= length * value;
}
float Vector2f::length() const
{
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0));
}
float Vector2f::lengthSquared() const
{
	return (x * x) + (y * y);
}
void Vector2f::power(float power)
{
	x = powf(x, power);
	y = powf(y, power);
}
void Vector2f::abs()
{
	if (x < 0)
		x *= -1.0f;
	if (y < 0)
		y *= -1.0f;
}

//static math functions
float Vector2f::DotProduct(const Vector2f &first, const Vector2f &second)
{
	return first.x * second.x + first.y * second.y;
}
float Vector2f::Distance(const Vector2f &first, const Vector2f &second)
{
	return sqrtf( (powf(second.x - first.x, 2.0f)) + (powf(second.y - first.y, 2.0f)) );	
}
float Vector2f::DistanceSquared(const Vector2f &first, const Vector2f &second)
{
	return (powf(second.x - first.x, 2.0f)) + (powf(second.y - first.y, 2.0f));
}
float Vector2f::AngleBetweenDegrees(const Vector2f &first, const Vector2f &second)
{
	float angle = atan2f(second.y - first.y, second.x - first.x);
	//Convert from radians to degrees
	angle*=((float)57.295779513082320876798154814105);
	return angle;
}
float Vector2f::AngleBetweenRadians(const Vector2f &first, const Vector2f &second)
{
	return atan2f(second.y - first.y, second.x - first.x);
}
Vector2f Vector2f::Midpoint(const Vector2f &first, const Vector2f &second)
{
	return Vector2f((first.x + second.x) * 0.5f, (first.y + second.y) * 0.5f);
}
Vector2f Vector2f::Quaterpoint(const Vector2f &first, const Vector2f &second)
{
	return Vector2f((first.x + second.x) * 0.25f, (first.y + second.y) * 0.25f);
}
Vector2f Vector2f::ThreeQuaterpoint(const Vector2f &first, const Vector2f &second)
{
	return Vector2f((first.x + second.x) * 0.75f, (first.y + second.y) * 0.75f);
}
Vector2f Vector2f::Betweenpoint(const Vector2f &first, const Vector2f &second, float value)
{
	return Vector2f((first.x + second.x) * value, (first.y + second.y) * value);
}
Vector2f Vector2f::Reciprical(const Vector2f &vector)
{
	return Vector2f( 1.0f / vector.x, 1.0f / vector.y);
}

void Vector2f::vectorArrayToFloatArray(float floatArray[], const Vector2f *vectorArray, int vectorArraySize)
{
	int n = 0;
	for (int i = 0; i < vectorArraySize; i++)
	{
		floatArray[n] = vectorArray[i].x;
		floatArray[n + 1] = vectorArray[i].y;
		n += 2;
	}
}