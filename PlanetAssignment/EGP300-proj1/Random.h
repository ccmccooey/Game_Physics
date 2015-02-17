#ifndef RANDOM_H
#define RANDOM_H

#include "Vector3f.h"

class Random
{
public:
	static int Range(int maxValue);
	static int Range(int minValue, int maxValue);
	static float ArithmeticFloat(); //get a random decimal between zero and one
	static float ArithmeticFloat(int decimalPrescision); //get a random decimal between zero and one
	static double ArithmeticDouble();
	static Vector3f Position(float maxX, float maxY, float maxZ);
	static Vector3f Position(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	static char RandomLetter();
	static char RandomDigit();
	static char RandomLetterOrDigit();

	static bool Bool();
	static bool Bool(int chance, int outOf);
};

#endif