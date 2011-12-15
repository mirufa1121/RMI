#include "EchoService_skeleton.h"

using namespace std;

EchoService_skeleton::EchoService_skeleton(EchoService *remote) {
	serverImpl = remote;
}

EchoService_skeleton::~EchoService_skeleton() {
	delete serverImpl;
}

char *EchoService_skeleton::invoke(char *buffer) {
	int methodSize = 0;
	memcpy(&methodSize, buffer, sizeof(int));
	
	char *retBuffer;
	int retSize = 0;
	
	if (methodSize > 0) {
		buffer += sizeof(int);
		
		char *methodNameCStr = new char[methodSize];
		memcpy(methodNameCStr, buffer, methodSize);
		
		string methodName(methodNameCStr, methodSize);
		delete methodNameCStr;
		buffer += methodSize;
		
		if (methodName == "echoTypes") {
			
			//cout << "Start EchoService_skeleton::invoke(echoTypes)" << endl;


			double d;
			float f;
			long nl, l;
			
			bool notDone = true;
			int check = 0;
			while (notDone) {
				if (buffer[0] == 'd') {
					buffer += 1;
					memcpy(&d, buffer, sizeof(double));
					buffer += sizeof(double);
					
					++check;
					if (check == 3)
						notDone = false;
				} else if (buffer[0] == 'f') {
					buffer += 1;
					memcpy(&f, buffer, sizeof(float));
					buffer += sizeof(float);
					
					++check;
					if (check == 3)
						notDone = false;
				} else if (buffer[0] == 'l') {
					buffer += 1;
					memcpy(&nl, buffer, sizeof(long));
					buffer += sizeof(long);
					
					l = ntohl( nl );
					
					++check;
					if (check == 3)
						notDone = false;
				}
			}
			
			char *response = serverImpl->echoTypes(d, f, l);
			
			int respSize = strlen(response);
			//cout << "echoTypes Response Size: " << respSize << endl; 
			retSize += respSize + sizeof(int);
			//cout << "echoTypes Return Size: " << retSize << endl;
			retBuffer = new char[retSize+sizeof(int)];
			
			memcpy(retBuffer, &retSize, sizeof(int));
			memcpy(retBuffer+sizeof(int), &respSize, sizeof(int));
			memcpy(retBuffer+2*sizeof(int), response, respSize);

			//cout << "End EchoService_skeleton:invoke(echoTypes)" << endl;
			

		} else if (methodName == "echoDoubleArray") {

			//cout << "Start EchoService_skeleton::invoke(echoDoubleArray)" << endl;


			int arraySize = 0;
			memcpy(&arraySize, buffer, sizeof(int));
			
			if (arraySize > 0) {
				buffer += sizeof(int);
				double *arr = new double[arraySize];
				int respSize = arraySize * sizeof(double);
				memcpy(arr, buffer, respSize);
				
				retBuffer = new char[respSize + sizeof(int)];
				memcpy(retBuffer, &respSize, sizeof(int));
				memcpy(retBuffer+sizeof(int), serverImpl->echoDoubleArray(arr, arraySize), arraySize*sizeof(double));
			
			}

			//cout << "End EchoService_skeleton::invoke(echoDoubleArray)" << endl;


		} else if (methodName == "echoTestObjectRef") {

			//cout << "Start EchoService_skeleton::invoke(echoTestObjectRef)" << endl;
			int i;
			double d;
			char c;

			memcpy(&i, buffer, sizeof(int));
			buffer += sizeof(int);

			memcpy(&d, buffer, sizeof(double));
			buffer += sizeof(double);

			memcpy(&c, buffer, sizeof(char));
			buffer += sizeof(char);

			TestObject obj(i, d, c);			
			obj = serverImpl->echoTestObjectRef(obj);

			int respSize = sizeof(int) + sizeof(double) + sizeof(char);
			retSize = respSize + sizeof(int);

			int saveInt = obj.getTestInt();
			double saveDouble = obj.getTestDouble();
			char saveChar = obj.getTestChar();

			retBuffer = new char[retSize+sizeof(int)];
			memcpy(retBuffer, &retSize, sizeof(int));
			memcpy(retBuffer+sizeof(int), &respSize, sizeof(int));
			memcpy(retBuffer+2*sizeof(int), &saveInt, sizeof(int));
			memcpy(retBuffer+3*sizeof(int), &saveDouble, sizeof(double));
			memcpy(retBuffer+3*sizeof(int)+sizeof(double), &saveChar, sizeof(char));

			//cout << "End EchoService_skeleton::invoke(echoTestObjectRef)" << endl;


		} else if (methodName == "echoTestObjectPtr") {

			//cout << "Start EchoService_skeleton::invoke(echoTestObjectPtr)" << endl;

			int i;
			double d;
			char c;

			memcpy(&i, buffer, sizeof(int));
			buffer += sizeof(int);
			
			memcpy(&d, buffer, sizeof(double));
			buffer += sizeof(double);

			memcpy(&c, buffer, sizeof(char));
			buffer += sizeof(char);

			TestObject *obj = new TestObject(i, d, c);			
			obj = serverImpl->echoTestObjectPtr(obj);

			int respSize = sizeof(int) + sizeof(double) + sizeof(char);
			retSize = respSize + sizeof(int);

			int saveInt = obj->getTestInt();
			double saveDouble = obj->getTestDouble();
			char saveChar = obj->getTestChar();

			retBuffer = new char[retSize+sizeof(int)];
			memcpy(retBuffer, &retSize, sizeof(int));
			memcpy(retBuffer+sizeof(int), &respSize, sizeof(int));       //
			memcpy(retBuffer+2*sizeof(int), &saveInt, sizeof(int)); 
			memcpy(retBuffer+3*sizeof(int), &saveDouble, sizeof(double));     //
			memcpy(retBuffer+3*sizeof(int)+sizeof(double), &saveChar, sizeof(char));      //


			//cout << "End EchoService_skeleton::(echoTestObjectPtr)" << endl;

		} else {
			cout << "Invalid method name." << endl;
			exit(-1);
		}

	}
	
	return retBuffer;
}
