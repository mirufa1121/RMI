all: Server.exe Client.exe Naming.exe

Skeleton.o: Skeleton.cpp Skeleton.h
	g++ -Wall -g -c Skeleton.cpp -o Skeleton.o

Naming.o: Naming.cpp Naming.h ClientCommunication.h EchoService_stub.h Naming_stub.h
	g++ -Wall -g -c Naming.cpp -o Naming.o

Naming_skeleton.o: Naming_skeleton.cpp Naming_skeleton.h Naming.h Skeleton.h
	g++ -Wall -g -c Naming_skeleton.cpp -o Naming_skeleton.o

Naming_stub.o: Naming_stub.cpp Naming_stub.h Naming.h
	g++ -Wall -g -c Naming_stub.cpp -o Naming_stub.o

NamingDriver.o: NamingDriver.cpp Naming.h UnicastRemoteObject.h
	g++ -Wall -g -c NamingDriver.cpp -o NamingDriver.o
	
Dispatcher.o: Dispatcher.cpp Dispatcher.h Skeleton.h
	g++ -Wall -g -c Dispatcher.cpp -o Dispatcher.o
	
RMITable.o: RMITable.cpp RMITable.h RMITableEntry.h Skeleton.h
	g++ -Wall -g -c RMITable.cpp -o RMITable.o

ServerDriver.o: ServerDriver.cpp EchoService.h Naming.h UnicastRemoteObject.h
	g++ -Wall -g -c ServerDriver.cpp -o ServerDriver.o
	
EchoService.o: EchoService.cpp EchoService.h
	g++ -Wall -g -c EchoService.cpp -o EchoService.o
	
EchoService_skeleton.o: EchoService_skeleton.cpp EchoService_skeleton.h Skeleton.h
	g++ -Wall -g -c EchoService_skeleton.cpp -o EchoService_skeleton.o
	
EchoService_stub.o: EchoService_stub.cpp EchoService_stub.h EchoService.h
	g++ -Wall -g -c EchoService_stub.cpp -o EchoService_stub.o
	
ClientDriver.o: ClientDriver.cpp Naming.h
	g++ -Wall -g -c ClientDriver.cpp -o ClientDriver.o
	
Endpoint.o: Endpoint.cpp Endpoint.h
	g++ -Wall -g -c Endpoint.cpp -o Endpoint.o
	
ClientCommunication.o: ClientCommunication.cpp ClientCommunication.h Endpoint.h
	g++ -Wall -g -c ClientCommunication.cpp -o ClientCommunication.o
	
TestObject.o: TestObject.cpp TestObject.h
	g++ -Wall -g -c TestObject.cpp -o TestObject.o

Naming.exe: TestObject.o Skeleton.o Naming.o Naming_skeleton.o NamingDriver.o Dispatcher.o RMITable.o EchoService.o EchoService_skeleton.o EchoService_stub.o ClientCommunication.o Endpoint.o
	g++ -Wall -g TestObject.o Skeleton.o Naming.o Naming_skeleton.o NamingDriver.o Dispatcher.o RMITable.o EchoService.o EchoService_skeleton.o EchoService_stub.o ClientCommunication.o Endpoint.o -o Naming.exe
	
Server.exe: TestObject.o Skeleton.o Naming.o Naming_stub.o Naming_skeleton.o Dispatcher.o RMITable.o ServerDriver.o EchoService.o EchoService_skeleton.o EchoService_stub.o ClientCommunication.o Endpoint.o
	g++ -Wall -g TestObject.o Skeleton.o Naming.o Naming_stub.o Naming_skeleton.o Dispatcher.o RMITable.o ServerDriver.o EchoService.o EchoService_skeleton.o EchoService_stub.o ClientCommunication.o Endpoint.o -o Server.exe
	
Client.exe: TestObject.o Skeleton.o Naming.o Naming_stub.o ClientDriver.o EchoService.o EchoService_stub.o ClientCommunication.o Endpoint.o
	g++ -Wall -g TestObject.o Skeleton.o Naming.o Naming_stub.o ClientDriver.o EchoService.o EchoService_stub.o ClientCommunication.o Endpoint.o -o Client.exe
	
clean:
	-rm *.o *.exe *~
