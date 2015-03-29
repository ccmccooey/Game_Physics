#pragma once
//Vector2f class written by Christopher McCooey
//WARNING, contains some pointless functions I added for fun of it
#include <ostream>

class Vector2f
{
public:
	float x;
	float y;

public:
	Vector2f();
	Vector2f(float x);
	Vector2f(float x, float y);
	Vector2f(const Vector2f &rhs);
	Vector2f(const Vector2f *rhs);
	Vector2f(const float xy[2]);
	~Vector2f();

	//setters
	void Set(float x, float y); //set all the values of the vector in a single line of a code

	//getters
	float getAngleY( const Vector2f& toVector );

	//operators overloads
	Vector2f& operator = ( const Vector2f& rhs );
	Vector2f& operator += ( const Vector2f& rhs );
	Vector2f& operator -= ( const Vector2f& rhs );
	Vector2f& operator *= ( const Vector2f& rhs );
	Vector2f& operator /= ( const Vector2f& rhs );
	Vector2f& operator *= ( float mult );
	Vector2f& operator /= ( float div );
	
	const Vector2f Vector2f::operator+(const Vector2f &other) const;
	const Vector2f Vector2f::operator-(const Vector2f &other) const;	
	const Vector2f Vector2f::operator*(const Vector2f &other) const;
	const Vector2f Vector2f::operator/(const Vector2f &other) const;
	const Vector2f Vector2f::operator*(float mult) const;
	const Vector2f Vector2f::operator/(float div) const;
	const Vector2f operator-() const;

	bool Vector2f::operator==(const Vector2f &other) const;
	bool Vector2f::operator!=(const Vector2f &other) const;

	friend std::ostream& Vector2f::operator<<(std::ostream& stream, const Vector2f& vector);
	std::string toString();
	void toArray(float floatArray[3]);

	//math functions
	float length() const;
	float lengthSquared() const;
	void normalize(); //make the vector length 1
	void lengthinize(float length); //make the vector length a specific value
	void power(float power);
	void abs();

	//static math functions
	static float DotProduct(const Vector2f &first, const Vector2f &second);
	static float Distance(const Vector2f &first, const Vector2f &second);
	static float DistanceSquared(const Vector2f &first, const Vector2f &second);
	static float AngleBetweenDegrees(const Vector2f &first, const Vector2f &second);
	static float AngleBetweenRadians(const Vector2f &first, const Vector2f &second);
	static float AngleBetweenPointsDegrees(const Vector2f &a, const Vector2f &b);
	static Vector2f Midpoint(const Vector2f &first, const Vector2f &second);
	static Vector2f Quaterpoint(const Vector2f &first, const Vector2f &second);
	static Vector2f ThreeQuaterpoint(const Vector2f &first, const Vector2f &second);
	static Vector2f Betweenpoint(const Vector2f &first, const Vector2f &second, float value); //value between 0 and 1
	static Vector2f Reciprical(const Vector2f &vector);
	static void vectorArrayToFloatArray(float floatArray[], const Vector2f *vectorArray, int vectorArraySize); //fill a float array from an array of vector3s

public:
	//constant vectors
	const static Vector2f zero;
	const static Vector2f one;
	const static Vector2f unitX;
	const static Vector2f unitY;
};

