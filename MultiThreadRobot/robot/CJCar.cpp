#include "arduino.h"
#include "CJCar.h"


CJCar::CJCar()
{
  gear = 1.0;
}

void CJCar::ChangeGear( float val )
{
  gear = val;  
}

void CJCar::MoveForward()//前进
{
  analogWrite(5, int(165 * gear)); //输入模拟值进行设定速度
  digitalWrite(7, LOW); //使直流电机（右）顺时针转
  digitalWrite(6, HIGH);
  analogWrite(11, int(160 * gear)); //输入模拟值进行设定速度
  digitalWrite(9, HIGH); //使直流电机（左）逆时针转
  digitalWrite(10, LOW);

  Serial.println("MoveForward");
}
void CJCar::MoveBackward()//前进
{
  analogWrite(5, int(165 * gear)); //输入模拟值进行设定速度
  digitalWrite(6, LOW); //使直流电机（右）顺时针转
  digitalWrite(7, HIGH);
  analogWrite(11, int(160 * gear)); //输入模拟值进行设定速度
  digitalWrite(10, HIGH); //使直流电机（左）逆时针转
  digitalWrite(9, LOW);

  Serial.println("MoveBackward");
}
void CJCar::Stop()//停止
{
  digitalWrite(6, HIGH); //使直流电机（右）制动
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH); //使直流电机（左）制动
  digitalWrite(10, HIGH);

  Serial.println("Stop");
}
void CJCar::TurnRight()//右转
{
  analogWrite(5, int(170 * gear)); //输入模拟值进行设定速度
  digitalWrite(6, LOW); //使直流电机（右）顺时针转
  digitalWrite(7, HIGH);
  analogWrite(11, int(150 * gear)); //输入模拟值进行设定速度
  digitalWrite(9, HIGH); //使直流电机（左）逆时针转
  digitalWrite(10, LOW);

  Serial.println("TurnRight");
}
void CJCar::TurnLeft()//左转
{
  analogWrite(5, int(150 * gear)); //输入模拟值进行设定速度
  digitalWrite(7, LOW); //使直流电机（右）顺时针转
  digitalWrite(6, HIGH);
  analogWrite(11, int(170 * gear)); //输入模拟值进行设定速度
  digitalWrite(10, HIGH); //使直流电机（左）逆时针转
  digitalWrite(9, LOW);

  Serial.println("TurnLeft");
}
