#include "ClientCommunication.h"

using namespace std;

ClientCommunication::ClientCommunication(Endpoint& serverEndpointIn) {
/**
* Used the CS 428 Socket tutorial (tcp-server.cc) as a reference
*/
	string hostIn = serverEndpointIn.getHost();
	int portIn = serverEndpointIn.getPort();
	serverEndpoint.setHost(hostIn);
	serverEndpoint.setPort(portIn);
}

int ClientCommunication::openConn() {
	struct sockaddr_in sin;
	struct hostent *hptr;

	if ((s = socket(AF_INET, SOCK_STREAM, 0 )) < 0) { /* create socket*/
  		cout << "Socket Error." << endl; /* socket error */
 		return -1;
	}
	sin.sin_family = AF_INET;              /*set protocol family to Internet */
	sin.sin_port = serverEndpoint.getPort();  /* set port no. */
	
	
	char *host = new char [serverEndpoint.getHost().size()+1];
	strcpy(host, serverEndpoint.getHost().c_str());
	
	if ((hptr =  gethostbyname(host)) == NULL){
    	cout << "Hostname Error." << endl; /* hostname error */
    	return -1;
	}

	memcpy(&sin.sin_addr, hptr->h_addr, hptr->h_length);

	if (connect (s, (struct sockaddr *)&sin, sizeof(sin)) < 0 ){
    	perror("connect");
    	return -1;
	}

	return 0;
}

char* ClientCommunication::sendMsg(char *callBuffer, int msgSize) {
	//cout << endl << "Start ClientCommunication::sendMsg()" << endl;
	//cout << endl << "Start Message Size: " << msgSize << endl;
		
	char msgStart = 'm';
	if (send(s, &msgStart, 1, 0) < 0) {
		perror("Message start");
		exit(-1);
	}
	
	if (send(s, &msgSize, sizeof(int),0) < 0) {  /* send message to server */
    	cout << "Send Error." << endl;
    	exit(-1); /*  write error */
   	}
	
	if (send(s, callBuffer, msgSize,0) < 0) {  /* send message to server */
    	cout << "Send Error." << endl;
    	exit(-1); /*  write error */
   	}
   	
   	int recvMsgSize;
   	
	if (( n = recv(s, &recvMsgSize, sizeof(int),0 ) ) <0) {  /* read message size from server */
    	cout << "Error Receiving Size of Response." << endl;
    	exit(-1);
	}
	
   	char *recvMsg = 0;

	if (recvMsgSize > 0) {
		recvMsg = new char[recvMsgSize];
		if (( n = recv(s, recvMsg, recvMsgSize,0)) < 0) {  /* read message from server */
			cout << "Error Receiving Response." << endl;
			exit(-1);
		}
	}

	//cout << endl << "End Message Size: " << recvMsgSize << endl;
	//cout << "End Buffer[0]: " << *recvMsg << endl;
	//cout << "End Buffer[1]: " << *(recvMsg+1) << endl;

	//cout << endl << "End ClientCommunication::sendMsg()" << endl << endl;

	return recvMsg;

}

string ClientCommunication::getHost() {
	return serverEndpoint.getHost();
}

int ClientCommunication::getPort() {
	return serverEndpoint.getPort();
}

void ClientCommunication::closeConn() {
	char closeConn = 'e';
	if (send(s, &closeConn, 1, 0) < 0) {
		perror("Connection close");
		exit(-1);
	}

	if (close(s) < 0) { 
		cout << "Connection Close Error." << endl;
   		exit(-1);
   	}
}



