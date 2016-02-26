#include "arduino.h"
#include "CJBluetooth.h"

//SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.


CJBluetooth::CJBluetooth()
{

}

void CJBluetooth::setup(int rx, int tx, long baurate)
{
    mBTserial = new SoftwareSerial(rx, tx); // RX | TX
    mBTserial->begin(baurate);

    //println("Bluetooth is ready \nRemember to select Both NL & CR in the serial monitor");
}


void CJBluetooth::println(String str)
{
  mBTserial->println(str);
}

SoftwareSerial* CJBluetooth::GetBtserial()
{
  return mBTserial;
}

