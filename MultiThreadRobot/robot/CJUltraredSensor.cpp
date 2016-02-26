#include "arduino.h"
#include "CJUltraredSensor.h"


CJUltraredSensor::CJUltraredSensor(int pin)
{
  mPin = pin;
}

//return distance (cm)
uint16_t CJUltraredSensor::GetDistance () 
{
    uint16_t value = analogRead (mPin);
    if (value < 70)  value = 70;
    return 12777.3/value-1.1;        //(cm)
    //return (62.5/(value/1023.0*5)-1.1);        //(cm)
    //return ((67870.0 / (value - 3.0)) - 40.0); //gp2d12 (mm)
}
