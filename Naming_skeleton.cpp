#include "Naming_skeleton.h"

using namespace std;

Naming_skeleton::Naming_skeleton(Naming *serverImplIn) {
	serverImpl = serverImplIn;
}

char *Naming_skeleton::invoke(char *buffer) {
	int methodSize = 0;
	memcpy(&methodSize, buffer, sizeof(int));
	
	char *retBuffer = 0;
	
	if (methodSize > 0) {
		buffer += sizeof(int);
		
		char *methodNameCStr = new char[methodSize];
		memcpy(methodNameCStr, buffer, methodSize);
		
		string methodName(methodNameCStr, methodSize);
		delete methodNameCStr;
		buffer += methodSize;
		
		if (methodName == "lookup") {
			int serviceSize = 0;
			memcpy(&serviceSize, buffer, sizeof(int));
			buffer += sizeof(int);

			if (serviceSize > 0) {
				char *serviceC = new char[serviceSize];
				memcpy(serviceC, buffer, serviceSize);
				buffer += serviceSize;
				
				string service(serviceC, serviceSize);
				EchoService_stub *stub = dynamic_cast<EchoService_stub *>(serverImpl->lookup(service));
				delete serviceC;

				string host = stub->getHost();
				int hostLen = host.length();
				
				// All members being sent on the wire
				char *hostC = new char[hostLen];
				strcpy(hostC, host.c_str());
				int port = stub->getPort();
				char flag = 'c';
				
				int msgSize = hostLen + 2*sizeof(int) + 1;
				retBuffer = new char[msgSize+sizeof(int)];

				memcpy(retBuffer, &msgSize, sizeof(int));
				int adder = sizeof(int);

				memcpy(retBuffer+adder, &flag, 1);
				adder += 1;

				memcpy(retBuffer+adder, &hostLen, sizeof(int));
				adder += sizeof(int);

				memcpy(retBuffer+adder, hostC, hostLen);
				adder += hostLen;

				memcpy(retBuffer+adder, &port, sizeof(int));

				delete hostC;
			}
		} else if (methodName == "bind") {
			int serviceSize = 0;
			memcpy(&serviceSize, buffer, sizeof(int));
			buffer += sizeof(int);

			if (serviceSize > 0) {
				char *serviceC = new char[serviceSize];
				memcpy(serviceC, buffer, serviceSize);
				buffer += serviceSize;
				
				string service(serviceC, serviceSize);
				
				int hostLen = 0;
				memcpy(&hostLen, buffer, sizeof(int));
				buffer += sizeof(int);

				if (hostLen > 0) {
					char *hostC = new char[hostLen];
					memcpy(hostC, buffer, hostLen);
					buffer += hostLen;

					int port = 0;
					memcpy(&port, buffer, sizeof(int));

					string host(hostC, hostLen);
					delete hostC;

					serverImpl->bind(service, host, port);
				}
			}
		} else {
			cout << "Invalid method name." << endl;
			exit(-1);
		}
	}
	
	return retBuffer;
}

Naming_skeleton::~Naming_skeleton() {
	delete serverImpl;
}
