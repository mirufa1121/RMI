// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef DISPATCHER_H__
#define DISPATCHER_H__

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "EchoService_skeleton.h"
#include "RMITable.h"

class Dispatcher {
private:
  RMITable *remoteTable;
protected:
public:
  // whatever methods you need
  Dispatcher(int portNumberIn);
  void waitOnPort(int);
  int handleConnection(int client);
};

#endif // DISPATCHER_H__
