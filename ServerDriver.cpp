
#include <iostream>
#include <unistd.h>

#include "EchoService.h"
#include "Naming_stub.h"
#include "UnicastRemoteObject.h"

using namespace std;

int main(int argc, char *argv[]) {

	cout << endl << "Starting Server" << endl;
	cout << "~~~~~~~~~~~~~~~" << endl << endl;
	
	// Arguments from command line missing
	if (argc < 4) {
		cout << "Host and port of the registry and the node name of the service are required command line arguments." << endl;
		return -1;
	}
	string host(argv[1]);
	int portNumber = atoi(argv[2]);
	string nodeName(argv[3]);

	cout << "Waiting for client on port " << portNumber << endl;
	
	EchoService *echoService = new EchoService();

	Endpoint e(host, portNumber);
	Naming *namingService = new Naming_stub(new ClientCommunication(e));
	string serviceName = "EchoService";

	int servicePort = 2500;

	namingService->bind(serviceName, nodeName, servicePort);
	UnicastRemoteObject::exportObject(echoService, servicePort, serviceName);
	
	// take care of memory management
	delete namingService;
	delete echoService;
	
	return 0;
}
