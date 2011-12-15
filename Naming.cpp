#include "Naming.h"

using namespace std;

Remote *Naming::lookup(string serviceName) {
	return stubRegistry.find(serviceName)->second;
}

void Naming::bind(string serviceName, string host, int port) {
	if (serviceName == "EchoService") {
		Endpoint e(host, port);
		ClientCommunication *cComm = new ClientCommunication(e);

		Remote *stub = new EchoService_stub(cComm);
		stubRegistry.insert(pair<string, Remote*>(serviceName, stub));
	}
}
