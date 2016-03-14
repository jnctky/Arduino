#include "arduino.h"
#include "CJCar.h"
#include "CJStepMotor.h"

class CJStepMotor
{


  CJStepMotor::CJStepMotor(int direction_pin, int step_pin)
  {
    mPinDir = direction_pin;
    mPinStep = step_pin;
    pinMode(mPinDir, OUTPUT);
    pinMode(mPinStep, OUTPUT);
    
    mLastDir = true;
    digitalWrite(mPinDir,HIGH);
    digitalWrite(mPinStep,LOW);
  }

  void ChangeDirection(bool direction)
  {
    if( mLastDir != dir) {
      mLastDir = dir;
      digitalWrite(mPinDir,dir);
      //delay(50);
    }
  }

  void StepOnce()
  {
    digitalWrite(stepperPin1, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin1, LOW);
  }

  void Step(bool dir,int steps)
  {

    if( mLastDir != dir) {
      mLastDir = dir;
      digitalWrite(mPinDir,dir);
      delay(50);
    }

    for(int i=0;i<steps;i++){
      digitalWrite(stepperPin1, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepperPin1, LOW);
      delayMicroseconds(100);
    }
  }

  int dirPin1 = 3;
  int stepperPin1 = 2;
  int dirPin2 = 7;
  int stepperPin2 = 6;
}