/* vim: set sts=2 sw=2 ts=8: */

#include "RMITable.h"
#include "RMITableEntry.h"
#include <assert.h>

using namespace std;

// redeclare the static variable
map<string, const RMITableEntry* > RMITable::remoteEntryMap;

RMITable::RMITable() {
}

void RMITable::addEntry(string uniqueID, RMITableEntry const* RMITableEntry){

  // two ways to do the same thing !!
  //    remoteEntryMap.insert(pair<string, RMITableEntry* >(uniqueID, RMITableEntry) );
  remoteEntryMap.insert(RemoteEntryMap::value_type(uniqueID, RMITableEntry));
}

const RMITableEntry* RMITable::getEntry(string uniqueID) {
  
  RemoteEntryMap::iterator it;
  
  const RMITableEntry* entry;
  
  it = remoteEntryMap.find(uniqueID);
  if (it != remoteEntryMap.end()) {
    entry = (*it).second;
  } else {
    // handle the error case
  }
  assert(entry != NULL);
  return const_cast<RMITableEntry *>(entry);
}

RMITable::~RMITable() {
  RemoteEntryMap::iterator it;
  
  for (it = remoteEntryMap.begin(); it != remoteEntryMap.end(); it++)
      delete it->second; 
}



