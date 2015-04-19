#include "UnitTest.h"
#include "Matrix33f.h"
#include <iostream>

using namespace std;

void UnitTest::RunTest()
{
	//test the matrix class
	cout << "===========================================================" << endl;
	cout << "================= Beginning Matrix33f =====================" << endl;

	cout << "identity: " << Matrix33f::identity << endl;
	cout << "zero: " << Matrix33f::zero << endl;
	cout << endl;
	
	Matrix33f expected;
	Matrix33f got;
	Matrix33f a;
	Matrix33f b;
	float detExpected;
	float detGot;

	//test multiplication
	a = Matrix33f(5, 4, 3, 1, 2, 0, 9, -4, 8);
	b = Matrix33f(7, 5, 3, 2, 1, 0, -4, -2, 9);
	expected = Matrix33f(31, 23, 42, 11, 7, 3, 23, 25, 99);
	got = a * b;

	cout << "------------------Testing (a X b) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	expected = Matrix33f(67, 26, 45, 11, 10, 6, 59, -56, 60);
	got = b * a;

	cout << "------------------Testing (b X a) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	//test the transpose function
	expected = Matrix33f(5, 1, 9, 4, 2, -4, 3, 0, 8);
	got = a.Transpose();

	cout << "------------------Testing (transpose A) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	//test the determinate
	detExpected = -18;
	detGot = a.Determinant();

	cout << "------------------Testing (determinate A) ------------------------" << endl;
	cout << "expected = " << detExpected << endl;
	cout << "answer   = " << detGot << endl;
	cout << endl;

	detExpected = -27;
	detGot = b.Determinant();

	cout << "------------------Testing (determinate B) ------------------------" << endl;
	cout << "expected = " << detExpected << endl;
	cout << "answer   = " << detGot << endl;
	cout << endl;
}

