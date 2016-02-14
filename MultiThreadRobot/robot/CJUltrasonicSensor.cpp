
#include "arduino.h"
#include "CJUltrasonicSensor.h"


CJUltrasonicSensor::CJUltrasonicSensor()
{
}

CJUltrasonicSensor::CJUltrasonicSensor(int mode, int inputPin, int outputPin)
{
  setMode(mode, inputPin, outputPin);
}

void CJUltrasonicSensor::setMode(int mode, int inputPin, int outputPin)
{
  mMode = mode;
  mInputPin = inputPin;
  mOutputPin = outputPin;

  if ( 2 == mMode ) {
    pinMode(mInputPin, INPUT);
    pinMode(mOutputPin, OUTPUT);
  }
}


int CJUltrasonicSensor::GetDistance()
{
  if( 1 == mMode ) {
    return GetDistanceMode1();
  } else if( 2 == mMode ) {
    return GetDistanceMode2();
  } else {
    return 0;
  }
}

//***********Private Functions***********
int CJUltrasonicSensor::GetDistanceMode1()
{
  //Mode1
  pinMode(mOutputPin,OUTPUT); //定义为输出接口
  digitalWrite(mOutputPin, LOW); //使发出发出超声波信号接口低电平2 μs
  delayMicroseconds(2);
  digitalWrite(mOutputPin, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(mOutputPin, LOW);     // 保持发出超声波信号接口低电平

  pinMode(mOutputPin, INPUT); //定义srfPin为输入接口
  int distance = pulseIn(mOutputPin, HIGH);  //  读出脉冲时间
  distance = distance / 58; // 将脉冲时间转化为距离（单位：厘米）

  return distance;
}

int CJUltrasonicSensor::GetDistanceMode2()
{
  //Mode2
  digitalWrite(mOutputPin, LOW); //使发出发出超声波信号接口低电平2 μs
  delayMicroseconds(2);
  digitalWrite(mOutputPin, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(mOutputPin, LOW);     // 保持发出超声波信号接口低电平
  int distance = pulseIn(mInputPin, HIGH);  //  读出脉冲时间
  distance = distance / 58; // 将脉冲时间转化为距离（单位：厘米）

  return distance;
}
