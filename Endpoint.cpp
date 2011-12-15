#include "Endpoint.h"

using namespace std;

Endpoint::Endpoint() {
	host = "localhost";
	port = 0;
}

Endpoint::Endpoint(string& hostIn, int portIn) {
	host = hostIn;
	port = portIn;
}

string Endpoint::getHost() {
	return host;
}

int Endpoint::getPort() {
	return port;
}

void Endpoint::setHost(string& hostIn) {
	host = hostIn;
}

void Endpoint::setPort(int portIn) {
	port = portIn;
}
