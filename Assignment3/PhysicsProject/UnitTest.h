//This is for testing all the math stuff

#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

class UnitTest
{
public:
	static void RunTest();

private:
	static void TestMatrix33f();
	static void TestMatrix44f();
	static void TestQuaternion();
};

#endif