// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef ECHO_SERVICE_SKELETON_H__
#define ECHO_SERVICE_SKELETON_H__

#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>

#include "EchoService.h"
#include "Skeleton.h"

class EchoService_skeleton : public Skeleton {

  private:
    EchoService *serverImpl;
  protected:
  public:
    // initialize the skeleton with a pointer to the server instance
    EchoService_skeleton(EchoService *remote);

    // unpack the buffer, invoke the service instance
    // then pack the return value and pack it back in the Buffer.
    char *invoke(char *buffer);


    ~EchoService_skeleton();
}; // end class EchoService_skeleton

#endif // ECHO_SERVICE_SKELETON_H__



