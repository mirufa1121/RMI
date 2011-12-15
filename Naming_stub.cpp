#include "Naming_stub.h"

using namespace std;

Naming_stub::Naming_stub(ClientCommunication *clientCommunicationIn) {
	clientCommunication = clientCommunicationIn;
	clientCommunication->openConn();
}

Remote * Naming_stub::lookup(string serviceName) {
	int uIDSize = 9;
	char *uID = "ServiceID";

	Remote *ret = NULL;
	int nameLen = serviceName.length();
	int methodSize = 6;

	char *service = new char[nameLen];
	strcpy(service, serviceName.c_str());
	char *method = "lookup";

	int msgSize = methodSize + nameLen + uIDSize + 3*sizeof(int);
	char *msg = new char[msgSize];

	int adder;		// Offset for the buffer pointer

	// Pack everything into a buffer to pass to the ClientCommuncation object
	memcpy(msg, &uIDSize, sizeof(int));
	adder = sizeof(int);

	memcpy(msg+adder, uID, uIDSize);
	adder += uIDSize;

	memcpy(msg+adder, &methodSize, sizeof(int));
	adder += sizeof(int);

	memcpy(msg+adder, method, methodSize);
	adder += methodSize;

	memcpy(msg+adder, &nameLen, sizeof(int));
	adder += sizeof(int);

	memcpy(msg+adder, service, nameLen);
	adder += nameLen;

	char *response = clientCommunication->sendMsg(msg, msgSize);

	delete service;
	delete msg;

	if (response != 0) {
		adder = 0;
		ClientCommunication *c;
		
		char flag = '0';
		memcpy(&flag, response+adder, 1);
		adder += 1;

		if (flag == 'c') {
			int hostSize = 0;
			memcpy(&hostSize, response+adder, sizeof(int));
			adder += sizeof(int);

			char *stubHostC = new char[hostSize];
			memcpy(stubHostC, response+adder, hostSize);
			adder += hostSize;

			int stubPort = 0;
			memcpy(&stubPort, response+adder, sizeof(int));
			adder += sizeof(int);

			string stubHost(stubHostC, hostSize);
			Endpoint e(stubHost, stubPort);

			c = new ClientCommunication(e);
			if (c->openConn() < 0) {
				cout << "Error connection to retrieved stub." << endl;
				exit(-1);
			}

			ret = new EchoService_stub(c);

			delete stubHostC;
		}
	}

	clientCommunication->closeConn();

	return ret;
}

void Naming_stub::bind(string serviceName, string host, int port) {
	int uIDSize = 9;
	char *uID = "ServiceID";

	int nameLen = serviceName.length();
	int hostLen = host.length();
	int methodSize = 4;

	char *service = new char[nameLen];
	char *hostC = new char[hostLen];

	strcpy(service, serviceName.c_str());
	strcpy(hostC, host.c_str());

	char *method = "bind";

	int msgSize = methodSize + nameLen + hostLen + uIDSize + 5*sizeof(int);
	char *msg = new char[msgSize];

	int adder = 0;		// Offset for the buffer pointer

	// Pack everything into a buffer to pass to the ClientCommuncation object
	memcpy(msg, &uIDSize, sizeof(int));
	adder = sizeof(int);

	memcpy(msg+adder, uID, uIDSize);
	adder += uIDSize;

	memcpy(msg+adder, &methodSize, sizeof(int));
	adder += sizeof(int);

	memcpy(msg+adder, method, methodSize);
	adder += methodSize;

	memcpy(msg+adder, &nameLen, sizeof(int));
	adder += sizeof(int);

	memcpy(msg+adder, service, nameLen);
	adder += nameLen;

	memcpy(msg+adder, &hostLen, sizeof(int));
	adder += sizeof(int);

	memcpy(msg+adder, hostC, hostLen);
	adder += hostLen;

	memcpy(msg+adder, &port, sizeof(int));
	adder += sizeof(int);

	clientCommunication->sendMsg(msg, msgSize);
	clientCommunication->closeConn();

	delete msg;
	delete hostC;
	delete service;
}

Naming_stub::~Naming_stub() {
	delete clientCommunication;
}
