// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef REMOTE_H__
#define REMOTE_H__

/**
 * All remote objects inherit from this class.
 **/

class Remote {

public:
  // need a virtual method so that
  // dynamic cast can work for classes
  // that inherit from this class
  virtual ~Remote() = 0;
};

inline Remote::~Remote() {}
// an explicit definition of  pure virtual destructor is required,
// or else it will result in a link error. 
// Depending on the compiler,
// it is also possible that a pure vitual destructor 
// with an explicit inline definition 
// will give a slight performance benefit, but that is compiler dependent.

#endif // REMOTE_H__


