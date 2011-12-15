#include <cstdlib>
#include <iostream>

#include "Naming.h"
#include "UnicastRemoteObject.h"

using namespace std;

int main(int argc, char *argv[]) {
	// Arguments from command line missing
	if (argc < 2) {
		cout << "Port of the registry are required command line arguments." << endl;
		return -1;
	}

	cout << endl << "Starting Naming Service" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int portNumber = atoi(argv[1]);

	cout << endl << "Waiting for connection on port " << portNumber << endl;
	
	Naming *namingService = new Naming();
	string serviceName = "Naming";
	
	// explicitly make the echoService remotely accessible
	// remoteHandle has all the information that needs to 
	// be sent to the registry in the "bind" call
	UnicastRemoteObject::exportObject(namingService, portNumber, serviceName);
	
	// take care of memory management
	delete namingService;
	
	return 0;
}
