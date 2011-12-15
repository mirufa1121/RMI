// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef ECHO_SERVICE_H__
#define ECHO_SERVICE_H__

#include <string>

#include "Remote.h"
#include "TestObject.h"

class EchoService : public Remote {

private:

public:

  EchoService();

  ~EchoService();

  virtual char* echoTypes(double dd, float ff, long ll);

  virtual TestObject echoTestObjectRef(TestObject& testObject); //const

  virtual TestObject* echoTestObjectPtr(TestObject* testObject);
  
  virtual double* echoDoubleArray(double doubleArray[], int arraySize);

  //virtual void* testObjPtr(void* bullshit);

};

#endif // ECHO_SERVICE_H__ 



