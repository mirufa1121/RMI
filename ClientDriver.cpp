// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#include "EchoService.h"
#include "Naming_stub.h"

using namespace std;

int main(int argc, char *argv[]) {

	cout << endl << "Starting Client" << endl;
	cout << "~~~~~~~~~~~~~~~" << endl;

	if (argc < 4) {
		cout << "Error: need host and port and service name of the registry" << endl;
		return -1;
	}

	// string host: get from the command line
	// string portNo: get from the command line
	// string uniqueServiceName: get from the command line

	string host = argv[1];
	int portNo = atoi(argv[2]);
	string serviceName = argv[3];

	cout << endl << "Requesting service on port " << portNo << endl;

	// lookupURL should point to the host and port 
	// of the registry. 

	Remote *remote = NULL;

	Endpoint e(host, portNo);
	Naming *naming = new Naming_stub(new ClientCommunication(e));

	// obtain a remote reference to echoService via the Naming service
	remote = naming->lookup(serviceName);

	EchoService* echoServer = dynamic_cast<EchoService *>(remote);

	double dd = 3.142857143;
	float ff = 12345;
	long ll = 54321;
	double doubleArray[10];
	for (int i=0; i<10; i++) {
		doubleArray[i] = i*1337;
	}
	int objInt = 6;
	double objDouble = 123.45;
	char objChar = 'y';

	string stringReturnValue = echoServer->echoTypes(dd, ff, ll);
	cout << endl << "-------------------------------------" << endl;
	cout << endl << "Requesting Service: echoTypes" << endl;
	cout << endl << "Sent Values:" << endl;
	cout << "\tDouble: " << dd << endl;
	cout << "\tFloat: " << ff << endl;
	cout << "\tLong: " << ll << endl;
	cout << endl << "Received String:" << endl;
	cout << "\t" << stringReturnValue << endl;


	double *returnDoubleArray = echoServer->echoDoubleArray(doubleArray, 10);
	cout << endl << "-------------------------------------" << endl;	
	cout << endl << "Requesting Service: echoDoubleArray" << endl;
	cout << endl << "Sent Double Array:" << endl;
	cout << "\t[";
	for (int i=0; i<10; i++) {
		if (i == 0)
			cout << doubleArray[i];
		else
			cout << ", " << doubleArray[i];
	}
	cout << "]" << endl;
	cout << endl << "Received Double Array:" << endl;
	cout << "\t[";
	for (int i=0; i<10; i++) {
		if (i == 0)
			cout << returnDoubleArray[i];
		else
			cout << ", " << returnDoubleArray[i];
	}
	cout << "]" << endl;

	TestObject testobj(objInt, objDouble, objChar);

	TestObject retObj = echoServer->echoTestObjectRef(testobj);
	cout << endl << "-------------------------------------" << endl;	
	cout << endl << "Requesting Service: echoTestObjectRef" << endl;
	cout << endl << "Sent Object Fields (Reference): " << endl;
	cout << "\tInt: " << objInt << endl;
	cout << "\tDouble: " << objDouble << endl;
	cout << "\tChar: " << objChar << endl;
	cout << endl << "Received Object Fields (Reference): " << endl;
	cout << "\tInt: " << retObj.getTestInt() << endl;
	cout << "\tDouble: " << retObj.getTestDouble() << endl;
	cout << "\tChar: " << retObj.getTestChar() << endl;

	TestObject* testobj1 = new TestObject(objInt, objDouble, objChar);

	TestObject* retObj1 = echoServer->echoTestObjectPtr(testobj1);
	cout << endl << "-------------------------------------" << endl;	
	cout << endl << "Requesting Service: echoTestObjectPtr" << endl;
	cout << endl << "Sent Object Fields (Pointer): " << endl;
	cout << "\tInt: " << objInt << endl;
	cout << "\tDouble: " << objDouble << endl;
	cout << "\tChar: " << objChar << endl;
	cout << endl << "Received Object Fields (Pointer): " << endl;
	cout << "\tInt: " << retObj1->getTestInt() << endl;
	cout << "\tDouble: " << retObj1->getTestDouble() << endl;
	cout << "\tChar: " << retObj1->getTestChar() << endl;

	delete remote;
	delete testobj1;
	delete naming;

	cout << endl << "-------------------------------------" << endl;
	cout << endl << "~~~~~~~~~~~~~" << endl;
	cout << "Client Closed" << endl << endl;

	return 0;
} // end main() ...


