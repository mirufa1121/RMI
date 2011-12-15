// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#ifndef RMI_TABLE_ENTRY_H__
#define RMI_TABLE_ENTRY_H__

#include "Skeleton.h"
#include "Remote.h"

class RMITableEntry {
  
private:
  
  Skeleton*  skeleton;
  Remote*  remote;
  
protected:
  
public:
  
  RMITableEntry() {}
  
  RMITableEntry(Skeleton *skeleton_, Remote* remote_) : skeleton(skeleton_), remote(remote_) {
  }
  
  inline Skeleton* getSkeleton() const {
    return this->skeleton;
  }
  
  inline  Remote* getRemote() const {
    return this->remote;
  }
  
  ~RMITableEntry() {
    delete skeleton;
    delete remote;
  }
};
#endif // RMI_TABLE_ENTRY_H__
