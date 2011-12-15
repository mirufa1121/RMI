#include "Dispatcher.h"

using namespace std;

Dispatcher::Dispatcher(int portNumberIn) {	
	waitOnPort(portNumberIn);
}

void Dispatcher::waitOnPort(int portNumber) {

	//cout << endl << "Start Dispatcher::waitOnPort()" << endl;

	int serv, client;		// Server and client
	unsigned int socklen;
	struct sockaddr_in sock;
	
	// Create the socket
	if ((serv = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Error creating socket." << endl;
		pthread_exit((void *) -1);
	}
	
	sock.sin_family = AF_INET;
	sock.sin_port = portNumber;
	sock.sin_addr.s_addr = INADDR_ANY;
	
	socklen = sizeof(sock);
	// Bind to sock
	if (bind(serv, (struct sockaddr *) &sock, socklen) < 0) {
		perror("Binding Error");
		cout << endl << "Error binding to address." << endl;
		exit(-1);
	}
	
	if (listen(serv, 5) < 0) {
		cout << "Error listening to port" << endl;
		exit(-1);
	}
	
	if (getsockname(serv, (struct sockaddr *)&sock, (socklen_t *) &socklen) == -1) {
		cout << "Error getting socket." << endl;
		exit(-1);
	}
	
	while (true) {
		// Accept new connections
		if ((client = accept(serv, (struct sockaddr *) &sock, (socklen_t *) &socklen)) < 0) {
			cout << "Error accepting connection." << endl;
			exit(-1);
		}
		
		cout << endl << "Accepted client #" << client << "." << endl << endl;
		if (handleConnection(client) < 0) {
			cout << "Error handling client " << client << "." << endl;
			exit(-1);
		}
		
		cout << endl << "Closed client #" << client << "." << endl;
		if (close(client) < 0) {
			cout << "Error closing client." << endl;
			exit(-1);
		}
	}

}

int Dispatcher::handleConnection(int client) {

	//cout << endl << "Start Dispatcher::handleConnection()" << endl;
	//cout << endl << "OO-------------------------------------" << endl;
	while (true) {
		char msgFlag = '0';
		if (recv(client, &msgFlag, 1, 0) < 0) {
			perror("Message flag");
			return -1;
		}
		
		if (msgFlag == 'e')
			break;
			
		else if (msgFlag == 'm') {
			int msgSize = 0;
			if (recv(client, &msgSize, sizeof(int), 0) < 0) {
				cout << "Error receiving message size." << endl;
				return -1;
			}			
			if (msgSize > 0) {
				char *buff = new char[msgSize];
				if (recv(client, buff, msgSize, 0) < 0) {
					cout << "Error receiving message." << endl;
					return -1;
				}
			
				int size = 0;
				memcpy(&size, buff, sizeof(int));
				
				if (size > 0) {
					char *uniqueID = new char[size];
					memcpy(uniqueID, buff+sizeof(int), size);
					
					string s(uniqueID, size);
					delete uniqueID;
					Skeleton *skeleton = Dispatcher::remoteTable->getEntry(s)->getSkeleton();
					
					char *response = skeleton->invoke(buff+size+sizeof(int));

					delete buff;
					
					int respSize = 0;
					if (response != 0) {
						memcpy(&respSize, response, sizeof(int));
						respSize = (int)respSize;						
						if (respSize > 0) {
							if (send(client, &respSize, sizeof(int), 0) < 0) {
								cout << endl;
								perror("Dispatcher send");
								return -1;
							}
							
							if (send(client, response+sizeof(int), respSize, 0) < 0) { 
								cout << endl;
								perror("Dispatcher send");
								return -1;
							}
						}
						
					} else {
						if (send(client, &respSize, sizeof(int), 0) < 0) {
							perror("Dispatcher send");
							return -1;
						}
					}
				} else
					return -1;
			}
		} else {
			cout << "Invalid message starter" << endl;
			break;
		}

		cout << endl;
	}
	
	//cout << "End Dispatcher::handleConnection()" << endl << endl;

	return 0;
}
