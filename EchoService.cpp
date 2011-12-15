// -*-c++-*-
// vim: set sts=2 sw=2 ts=8: 

#include "EchoService.h"
#include <iostream>

using namespace std;

EchoService::EchoService() {
}

EchoService::~EchoService() {
	
}

char * EchoService::echoTypes(double dd, float ff, long ll) {

      //cout << "Start EchoService::echoTypes()" << endl;
      cout << endl << "-------------------------------------" << endl;
      cout << endl << "Service Requested: echoTypes" << endl;
      cout << endl << "Values Received:" << endl;
      cout << "\tDouble: " << dd << endl;
      cout << "\tFloat: " << ff << endl;
      cout << "\tLong: " << ll << endl;
      cout << endl << "String Returned:" << endl;
      cout << "\t" << "Introduction to Dist Systems: fun with RMI" << endl;
      char *returnValue = "Introduction to Dist Systems: fun with RMI";
      //cout << endl << "End EchoService::echoTypes()" << endl;

      return  returnValue;
}

TestObject EchoService::echoTestObjectRef(TestObject& testObject) { // const

      //cout << "Start EchoService::echoTestObjectRef()" << endl;
      int intField = testObject.getTestInt();
      double dubField = testObject.getTestDouble();
      char charField = testObject.getTestChar();

      cout << endl << "-------------------------------------" << endl;      
      cout << endl << "Service Requested: echoTestObjectRef" << endl;
      cout << endl << "Reference Object Fields (Original): " << endl;
      cout << "\tInt: " << intField << endl;
      cout << "\tDouble: " << dubField << endl;
      cout << "\tChar: " << charField << endl;

      testObject.setTestInt(intField + 1);
      testObject.setTestDouble(dubField + 1);
      testObject.setTestChar(charField + 1);

      cout << endl << "Reference Object Fields (New): " << endl;
      cout << "\tInt: " << testObject.getTestInt() << endl;
      cout << "\tDouble: " << testObject.getTestDouble() << endl;
      cout << "\tChar: " << testObject.getTestChar() << endl;

      //cout << endl << "End EchoService::echoTestObjectRef()" << endl;
      
      return testObject;
}
     
TestObject* EchoService::echoTestObjectPtr(TestObject* testObject) {

      //cout << "Start EchoService::echoTestObjectPtr()" << endl;
      cout << endl << "-------------------------------------" << endl;
      cout << endl << "Service Requested: echoTestObjectPtr" << endl;

      int intField = testObject->getTestInt();
      double dubField = testObject->getTestDouble();
      char charField = testObject->getTestChar();
      
      cout << endl << "Pointer Object Fields (Original): " << endl;
      cout << "\tInt: " << intField << endl;
      cout << "\tDouble: " << dubField << endl;
      cout << "\tChar: " << charField << endl;

      testObject->setTestInt(intField - 1);
      testObject->setTestDouble(dubField - 1);
      testObject->setTestChar(charField - 1);

      cout << endl << "Pointer Object Fields (New): " << endl;
      cout << "\tInt: " << testObject->getTestInt() << endl;
      cout << "\tDouble: " << testObject->getTestDouble() << endl;
      cout << "\tChar: " << testObject->getTestChar() << endl;

      cout << endl << "-------------------------------------" << endl;
      //cout << endl << "End EchoService::echoTestObjectPtr()" << endl;

      return testObject;
}
     
     
double* 
EchoService::echoDoubleArray(double doubleArray[], int arraySize) {

      //cout << "Start EchoService::echoDoubleArray()" << endl;
      cout << endl << "-------------------------------------" << endl;
      cout << endl << "Service Requested: echoDoubleArray" << endl;

      double *returnArray = new double[arraySize];

      for (int i=0; i<10; i++) {
            returnArray[i] = doubleArray[i] * 2;
      }

      cout << endl << "Double Array Received:" << endl;
      for (int i=0; i<10; i++) {
            if (i == 0)
                  cout << "\t[" << doubleArray[i];
            else
                  cout << ", " << doubleArray[i];
      }
      cout << "]" << endl;
      cout << endl << "Double Array Returned:" << endl;
      for (int i=0; i<10; i++) {
            if (i == 0)
                  cout << "\t[" << returnArray[i];
            else
                  cout << ", " << returnArray[i];
      }
      cout << "]" << endl;
      //cout << endl << "End EchoService::echoDoubleArray()" << endl;

      return returnArray;    
}

/* void*
EchoService::testObjPtr(void* eyo) {
      cout << eyo << endl;

      return eyo;
}
     
*/


