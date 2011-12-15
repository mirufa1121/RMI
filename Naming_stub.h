// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef NAMING_STUB_H__
#define NAMING_STUB_H__

#include <cstring>

#include "Naming.h"

class Naming_stub : public Naming {

private:
  ClientCommunication *clientCommunication;

protected:

public:

  // constructor. This stub should be initilaized with a
  // communication object, that knows how to connect to the
  // server side
  Naming_stub(ClientCommunication *clientCommunicationIn);

  Remote* lookup(std::string serviceName);
  
  void bind(std::string serviceName, std::string host, int port);

  ~Naming_stub();

};

#endif // NAMING_STUB_H__


