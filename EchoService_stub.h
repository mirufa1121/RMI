// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef ECHO_SERVICE_STUB_H__
#define ECHO_SERVICE_STUB_H__

#include "ClientCommunication.h"
#include "EchoService.h"

class EchoService_stub : public EchoService {

private:
  ClientCommunication* clientCommunication;
  
protected:
  
public:
  EchoService_stub();
  // constructor. This stub should be initilaized with a
  // communication object, which knows how to connect to the
  // server side
  EchoService_stub(ClientCommunication *clientCommunicationIn);

  // all methods from the EchoService interface
  char *echoTypes(double dd, float ff, long ll);

  TestObject* echoTestObjectPtr(TestObject* testObject);

  TestObject echoTestObjectRef(TestObject& testObject);

  double *echoDoubleArray(double doubleArray[], int arraySize);

  std::string getHost();
  int getPort();
  
  // destructor
 ~EchoService_stub();
};

#endif // ECHO_SERVICE_STUB_H__


