#include "EchoService_stub.h"

using namespace std;

EchoService_stub::EchoService_stub(ClientCommunication *clientCommunicationIn) {
	clientCommunication = clientCommunicationIn;
}

char *EchoService_stub::echoTypes(double dd, float ff, long ll){
	//cout << endl << "Start EchoService_stub::echoTypes()" << endl;

	int uIDSize = 9;
	char *uID = "ServiceID";
	int methNameSize = 9;
	char *methName = "echoTypes";
	char indD = 'd';
	double doubleVal = dd;
	char indF = 'f';
	float floatVal = ff;
	char indL = 'l';
	long longVal = htonl(ll);
	
	int msgSize = 2*sizeof(int) + uIDSize + methNameSize +
					sizeof(double) + sizeof(float) + sizeof(long) + 3;
	
	char *Buffer = new char[msgSize];
	char *Temp = Buffer;
	
	memcpy(Temp, &uIDSize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, uID, uIDSize);
	Temp += uIDSize;
	
	memcpy(Temp, &methNameSize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, methName, methNameSize);
	Temp += methNameSize;
	
	memcpy(Temp, &indD, 1);
	Temp += 1;
	
	memcpy(Temp, &doubleVal, sizeof(double));
	Temp += sizeof(double);
	
	memcpy(Temp, &indF, 1);
	Temp += 1;
	
	memcpy(Temp, &floatVal, sizeof(float));
	Temp += sizeof(float);
	
	memcpy(Temp, &indL, 1);
	Temp += 1;
	
	memcpy(Temp, &longVal, sizeof(long));
	
	char *response = clientCommunication->sendMsg(Buffer, msgSize);

	int respSize = 0;

	memcpy(&respSize, response, sizeof(int));
	
	char *str;
	if (respSize > 0) {
		str = new char[respSize];
		memcpy(str, response+sizeof(int), respSize);
	} else
		str = "Error";
	
	delete Buffer;

	//cout << endl << "End EchoService_stub::echoTypes()" << endl;

	return str;
}

double *EchoService_stub::echoDoubleArray(double doubleArray[], int arraySize) {
	//cout << endl << "Start EchoService_stub::echoDoubleArray()" << endl;

	int uIDSize = 9;
	char *uID = "ServiceID";
	int methNameSize = 15;
	char *methName = "echoDoubleArray";
	
	int msgSize = 3*sizeof(int) + uIDSize + methNameSize + arraySize*sizeof(double);
	
	char *Buffer = new char[msgSize];
	char *Temp = Buffer;
	
	memcpy(Temp, &uIDSize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, uID, uIDSize);
	Temp += uIDSize;
	
	memcpy(Temp, &methNameSize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, methName, methNameSize);
	Temp += methNameSize;
	
	memcpy(Temp, &arraySize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, doubleArray, arraySize*sizeof(double));
	
	char *response = clientCommunication->sendMsg(Buffer, msgSize);
	
	double *retArray = new double[arraySize];
	memcpy(retArray, response, arraySize*sizeof(double));
	
	delete Buffer;

	//cout << endl << "End EchoService_stub::echoDoubleArray()" << endl;

	return retArray;
}

TestObject *EchoService_stub::echoTestObjectPtr(TestObject* testObject) {
	//cout << endl << "Start EchoService_stub::echoTestObjectPtr()" << endl;
	int testIntSize = sizeof(int);
	int testDoubleSize = sizeof(double);
	int testCharSize = sizeof(char);
	int testInt = testObject->getTestInt();
	double testDouble = testObject->getTestDouble();
	char testChar = testObject->getTestChar();

	int uIDSize = 9;
	char *uID = "ServiceID";
	char *methName = "echoTestObjectPtr";
	int methNameSize = 17;

	int msgSize = testIntSize + testDoubleSize + testCharSize + methNameSize + uIDSize + 2*sizeof(int);

	char *Buffer = new char[msgSize];
	char *Temp = Buffer;

	memcpy(Temp, &uIDSize, sizeof(int));
	Temp += sizeof(int);

	memcpy(Temp, uID, uIDSize);
	Temp += uIDSize;

	memcpy(Temp, &methNameSize, sizeof(int));
	Temp += sizeof(int);

	memcpy(Temp, methName, methNameSize);
	Temp += methNameSize;

	memcpy(Temp, &testInt, testIntSize);
	Temp += testIntSize;

	memcpy(Temp, &testDouble, testDoubleSize);
	Temp += testDoubleSize;

	memcpy(Temp, &testChar, testCharSize);

	char *response = clientCommunication->sendMsg(Buffer, msgSize);

	int rspInt = 0;
	double rspDouble = 0;
	char rspChar = 0;
	int respSize = 0;
	
	memcpy(&respSize, response, sizeof(int));
	response += sizeof(int);

	//cout << "Response Size: " << respSize << endl;

	memcpy(&rspInt, response, sizeof(int));
	response += sizeof(int);

	memcpy(&rspDouble, response, sizeof(double));
	response += sizeof(double);

	memcpy(&rspChar, response, sizeof(char));

	//cout << "Returned int: " << rspInt << endl;
	//cout << "Returned double: " << rspDouble << endl;
	//cout << "Returned char: " << rspChar << endl;

	TestObject* retObj = new TestObject(rspInt, rspDouble, rspChar);

	//cout << "End EchoService_stub::echoTestObjectPtr()" << endl << endl;

	return retObj;
}

TestObject EchoService_stub::echoTestObjectRef(TestObject& testObject) {
	//cout << endl << "Start EchoService_stub::echoTestObjectRef()" << endl;
	int testIntSize = sizeof(int);
	int testDoubleSize = sizeof(double);
	int testCharSize = sizeof(char);
	int testInt = testObject.getTestInt();
	double testDouble = testObject.getTestDouble();
	char testChar = testObject.getTestChar();

	int uIDSize = 9;
	char *uID = "ServiceID";
	char *methName = "echoTestObjectRef";
	int methNameSize = 17;

	int msgSize = sizeof(int) + sizeof(double) + sizeof(char) + methNameSize + uIDSize + 2*sizeof(int);

	char *Buffer = new char[msgSize];
	char *Temp = Buffer;

	memcpy(Temp, &uIDSize, sizeof(int));
	Temp += sizeof(int);

	memcpy(Temp, uID, uIDSize);
	Temp += uIDSize;

	memcpy(Temp, &methNameSize, sizeof(int));
	Temp += sizeof(int);
	
	memcpy(Temp, methName, methNameSize);
	Temp += methNameSize;

	memcpy(Temp, &testInt, sizeof(int));
	Temp += sizeof(int);

	memcpy(Temp, &testDouble, sizeof(double));
	Temp += sizeof(double);

	memcpy(Temp, &testChar, sizeof(char));

	char *response = clientCommunication->sendMsg(Buffer, msgSize);

	int respSize = 0;
	int rspInt;
	double rspDouble;
	char rspChar;

	memcpy(&respSize, response, sizeof(int));
	response += sizeof(int);

	memcpy(&rspInt, response, sizeof(int));
	response += sizeof(int);

	memcpy(&rspDouble, response, sizeof(double));
	response += sizeof(double);

	memcpy(&rspChar, response, sizeof(char));

	TestObject retObj(rspInt, rspDouble, rspChar);

	//cout << "End EchoService_stub::echoTestObjectRef()" << endl;

	return retObj;
	}

string EchoService_stub::getHost() {
	return clientCommunication->getHost();
}

int EchoService_stub::getPort() {
	return clientCommunication->getPort();
}

EchoService_stub::~EchoService_stub() {
	clientCommunication->closeConn();
	delete clientCommunication;
}
