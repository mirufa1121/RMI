// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef NAMING_SKELETON_H__
#define NAMING_SKELETON_H__

#include <cstring>
#include <string>

#include "EchoService_stub.h"
#include "Naming.h"
#include "Skeleton.h"

class Naming_skeleton : public Skeleton {
  private:
    Naming *serverImpl;
  protected:
  public:
    // initialize the skeketon with a pointer to the server instance
    Naming_skeleton(Naming *remote);

   // dispatch  the call, get the return value, pack it in Buffer
    char *invoke(char *buffer);
    ~Naming_skeleton();
}; // end class Naming_skeleton

#endif // NAMING_SKELETON_H__
