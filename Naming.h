
// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 


#ifndef NAMING_H__
#define NAMING_H__

#include <map>

#include "EchoService_stub.h"

class Naming : public Remote {

private:
	std::map<std::string, Remote *> stubRegistry;
protected:
public:
  	virtual Remote* lookup(std::string serviceName);
  	virtual void bind(std::string, std::string, int);
};

#endif // NAMING_H__

