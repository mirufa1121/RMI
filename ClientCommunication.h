// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <cstring>

#include "Endpoint.h"

#ifndef CLIENT_COMMUNICATION_H__
#define CLIENT_COMMUNICATION_H__

class ClientCommunication {
private:
  Endpoint serverEndpoint;
protected:
public:
  int s;
  int n;
  ClientCommunication(Endpoint& serverEndpoint);
  std::string getHost();
  int getPort();
  char* sendMsg(char *callBuffer, int msgSize);
  int openConn();
  void closeConn();
};

#endif // CLIENT_COMMUNICATION_H__
