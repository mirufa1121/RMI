#include "Dispatcher.h"
#include "EchoService_skeleton.h"
#include "Naming_skeleton.h"
#include "RMITable.h"

class UnicastRemoteObject {
	public:
		static void exportObject(Remote *remoteService, int portNumber, std::string& serviceName) {
			std::string uniqueID = "ServiceID";
			Skeleton *skeleton = NULL;

			if (serviceName == "Naming")
				skeleton = new Naming_skeleton((Naming *) remoteService);
			else if (serviceName == "EchoService") {
				skeleton = new EchoService_skeleton((EchoService *)remoteService);
			}
			
			if (skeleton != NULL) {
				RMITableEntry *tableEntry = new RMITableEntry(skeleton, remoteService);
				RMITable *table;
				
				table->addEntry(uniqueID, tableEntry);
				
				new Dispatcher(portNumber);
			}
		}
};
