#include "arduino.h"
#include "CJDebugger.h"

//SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.

int CJDebugger::mPort = DEBUG_PORT_NONE;
SoftwareSerial *CJDebugger::mBTserial = new SoftwareSerial(2, 3);

CJDebugger::CJDebugger()
{

}

void CJDebugger::setup(int port, long baurate)
{
  mPort = port;

  if (DEBUG_PORT_SERIAL == mPort) {
    Serial.begin(baurate);
  } else if (DEBUG_PORT_BLUETOOTH == mPort) {
    //mBTserial = new SoftwareSerial(2, 3); // RX | TX
    mBTserial->begin(baurate);
  }

  println("Arduino is ready \nRemember to select Both NL & CR in the serial monitor");

}


void CJDebugger::println(String str)
{
  if (DEBUG_PORT_SERIAL == mPort) {
    Serial.println(str);
  } else if (DEBUG_PORT_BLUETOOTH == mPort) {
    mBTserial->println(str);
  } else {
    // do nothing
  }
  
}

