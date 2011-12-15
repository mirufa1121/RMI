#ifndef RMI_TABLE_H__
#define RMI_TABLE_H__

#include "RMITableEntry.h"
#include <map>
#include <string>

class RMITable {
  
private:
  typedef std::map<std::string, const RMITableEntry* > RemoteEntryMap;
  static RemoteEntryMap remoteEntryMap;
  
protected:
public:
  RMITable();
  ~RMITable();
  
  static void addEntry(std::string uniqueID, const RMITableEntry* );
  static const RMITableEntry* getEntry(std::string uniqueID);
};

#endif // RMI_TABLE_H__

