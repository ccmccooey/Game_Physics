#include "Random.h"
#include <iostream>

int Random::Range(int maxValue)
{
	return (rand() % maxValue);
}
int Random::Range(int minValue, int maxValue)
{
	return (rand() % (maxValue - minValue)) + minValue;
}
float Random::ArithmeticFloat()
{
	float value = (float)(rand() % 10000000) / 10000000.0f;
	return value;
}
double Random::ArithmeticDouble()
{
	double value = (double)(rand() % 10000000) / 10000000.0f;
	return value;
}
float Random::ArithmeticFloat(int decimalPrescision)
{
	int tmp = 10 * decimalPrescision;
	return (float)(rand() % tmp) / (float)tmp;
}
Vector3f Random::Position(float maxX, float maxY, float maxZ)
{
	Vector3f vec = Vector3f();
	vec.x = (float)Range((int)maxX);
	vec.y = (float)Range((int)maxY);
	vec.z = (float)Range((int)maxZ);
	return vec;
}
Vector3f Random::Position(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	Vector3f vec = Vector3f();
	vec.x = (float)Range((int)minX, (int)maxX);
	vec.y = (float)Range((int)minY, (int)maxY);
	vec.z = (float)Range((int)minZ, (int)maxZ);
	return vec;
}



char Random::RandomLetter()
{
	char range = 'Z' - 'A';
	int value = rand() % (int)range + (int)'A';
	return (char)value;
}
char Random::RandomDigit()
{
	char range = '9' - '0';
	int value = rand() % (int)range + (int)'0';
	return (char)value;
}
char Random::RandomLetterOrDigit()
{
	int value = rand() % 3;
	char c = 'A';
	if (value == 0)
	{
		c = RandomDigit();
	}
	else
	{
		c = RandomLetter();
	}
	return c;
}


bool Random::Bool()
{
	return rand() % 2 == 0;
}
bool Random::Bool(int chance, int outOf)
{
	return rand() % outOf <= chance - 1;
}