#include "UnitTest.h"
#include "Matrix33f.h"
#include "Matrix44f.h"
#include "Quaternion.h"
#include <iostream>

using namespace std;

void UnitTest::RunTest()
{
	UnitTest::TestMatrix33f();
	UnitTest::TestMatrix44f();
	UnitTest::TestQuaternion();
}

void UnitTest::TestMatrix33f()
{
	//test the matrix33 class
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

	//test inverse
	expected = Matrix33f(-0.8889f, 2.4444f, 0.3333f, 0.4444f, -7.222f, -0.1667f, 1.2222f, -3.1111f, -0.3333f);
	got = Matrix33f();
	got.SetInverse(a);

	cout << "------------------Testing (inverse A) ------------------------" << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;
		
	cout << endl;
}
void UnitTest::TestMatrix44f()
{
	//test the matrix44 class
	cout << "===========================================================" << endl;
	cout << "================= Beginning Matri44f =====================" << endl;

	cout << "identity: " << Matrix44f::identity << endl;
	cout << "zero: " << Matrix44f::zero << endl;
	cout << endl;
	
	Matrix44f expected;
	Matrix44f got;
	Matrix44f a;
	Matrix44f b;
	float detExpected;
	float detGot;

	//test multiplication
	a = Matrix44f(0, 2, 7, 4, 1, -4, 3, 5, 9, 8, -3, -1, -5, -7, -9, 10);
	b = Matrix44f(8, -4, 2, 4, -3, 3, -2, 0, 1, -5, 6, 5, -8, -9, 9, 7);
	expected = Matrix44f(-31, -65, 74, 63, -17, -76, 73, 54, 53, 12, -25, 14, -108, -46, 40, 5);
	got = a * b;

	cout << "------------------Testing (a X b) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	expected = Matrix44f(-6, 20, 2, 50, -15, -34, -6, 5, 24, 35, -71, 23, 37, 43, -173, -16);
	got = b * a;
	cout << "------------------Testing (b X a) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	//test the transpose function
	expected = Matrix44f(0, 1, 9, -5, 2, -4, 8, -7, 7, 3, -3, -9, 4, 5, -1, 10);
	got = a.Transpose();

	cout << "------------------Testing (transpose A) ------------------------" << endl;
	cout << "a = " << a << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	//test the determinate
	detExpected = 5818;
	detGot = a.Determinant();

	cout << "------------------Testing (determinate A) ------------------------" << endl;
	cout << "expected = " << detExpected << endl;
	cout << "answer   = " << detGot << endl;
	cout << endl;

	detExpected = 558;
	detGot = b.Determinant();

	cout << "------------------Testing (determinate B) ------------------------" << endl;
	cout << "expected = " << detExpected << endl;
	cout << "answer   = " << detGot << endl;
	cout << endl;

	cout << endl;
}

void UnitTest::TestQuaternion()
{
	//test euler angles
	Vector3f eulerAnglesDegrees;
	Quaternion got;
	Quaternion expected;

	cout << "===========================================================" << endl;
	cout << "================= Beginning Quaternions =====================" << endl;

	expected = Quaternion(0.70711f, 0.70711f, 0.0f, 0.0f);
	got = Quaternion();
	eulerAnglesDegrees = Vector3f(90.0f, 0.0f, 0.0f);
	got.setEulerDeg(eulerAnglesDegrees.x, eulerAnglesDegrees.y, eulerAnglesDegrees.z);

	cout << "------------------Testing (euler angles degrees to quaternion) ------------------------" << endl;
	cout << "euler angles degrees = " << eulerAnglesDegrees << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;

	expected = Quaternion(0.5684899206203877f, -0.006520341738628904f, 0.6156582687007653f, 0.5456570273321997f);
	got = Quaternion();
	eulerAnglesDegrees = Vector3f(70.0f, 45.0f, 120.0f);
	got.setEulerDeg(eulerAnglesDegrees.x, eulerAnglesDegrees.y, eulerAnglesDegrees.z);

	cout << "------------------Testing (euler angles degrees to quaternion) ------------------------" << endl;
	cout << "euler angles degrees = " << eulerAnglesDegrees << endl;
	cout << "expected = " << expected << endl;
	cout << "answer   = " << got << endl;
	cout << endl;
}

