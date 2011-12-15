#include "TestObject.h"

using namespace std;

TestObject::TestObject() {}

TestObject::TestObject(int n, double d, char c) {
	testInt = n;
	testDouble = d;
	testChar = c;
}

int TestObject::getTestInt() {
	return testInt;
}

double TestObject::getTestDouble() {
	return testDouble;
}

char TestObject::getTestChar() {
	return testChar;
}

void TestObject::setTestInt(int n) {
	testInt = n;
}

void TestObject::setTestDouble(double d) {
	testDouble = d;
}

void TestObject::setTestChar(char c) {
	testChar = c;
}

