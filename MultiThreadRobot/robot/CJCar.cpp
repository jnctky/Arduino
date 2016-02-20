#include "arduino.h"
#include "CJCar.h"

#define START_DELAY_MS   50
#define STEP_1DEGREE_MS  8

#define A_SPEED  (150*0.75)
#define B_SPEED  (170*0.75)

CJCar::CJCar(int enA, int in1, int in2, int enB, int in3, int in4)
{
  mPinEnA = enA;
  mPinIn1 = in1;
  mPinIn2 = in2;
  mPinEnB = enB;
  mPinIn3 = in3;
  mPinIn4 = in4;
  gear = 1.0;

  //双H桥马达驱动信号输出
  pinMode(mPinEnA, OUTPUT); //定义EA(PWM调速)接口
  pinMode(mPinIn1, OUTPUT); //定义EA(PWM调速)接口
  pinMode(mPinIn2, OUTPUT); //定义EA(PWM调速)接口
  pinMode(mPinEnB, OUTPUT); //定义EA(PWM调速)接口
  pinMode(mPinIn3, OUTPUT); //定义EA(PWM调速)接口
  pinMode(mPinIn4, OUTPUT); //定义EA(PWM调速)接口

  /*
  pinMode(5, OUTPUT); //定义EA(PWM调速)接口
  pinMode(7, OUTPUT); //定义I1接口
  pinMode(6, OUTPUT); //定义I2接口

  pinMode(11, OUTPUT); //定义EB(PWM调速)接口
  pinMode(9, OUTPUT); //定义I3接口
  pinMode(10, OUTPUT); //定义I4接口
  */
  
}

void CJCar::ChangeGear( float val )
{
  gear = val;  
}

void CJCar::MoveForward()//前进
{
  analogWrite(mPinEnA, int(A_SPEED * gear) ); //输入模拟值进行设定速度
  digitalWrite(mPinIn1, LOW); //使直流电机（右）顺时针转
  digitalWrite(mPinIn2, HIGH);
  analogWrite(mPinEnB, int(B_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn3, HIGH); //使直流电机（左）逆时针转
  digitalWrite(mPinIn4, LOW);

  Serial.println("MoveForward");
}
void CJCar::MoveBackward()//前进
{
  analogWrite(mPinEnA, int(A_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn2, LOW); //使直流电机（右）顺时针转
  digitalWrite(mPinIn1, HIGH);
  analogWrite(mPinEnB, int(B_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn4, HIGH); //使直流电机（左）逆时针转
  digitalWrite(mPinIn3, LOW);

  Serial.println("MoveBackward");
}
void CJCar::Stop()//停止
{
  digitalWrite(mPinIn2, HIGH); //使直流电机（右）制动
  digitalWrite(mPinIn1, HIGH);
  digitalWrite(mPinIn3, HIGH); //使直流电机（左）制动
  digitalWrite(mPinIn4, HIGH);

  Serial.println("Stop");
}

int CJCar::TurnRight(int degree)//右转
{ 
  int millis = 0;
  
  analogWrite(mPinEnA, int(A_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn2, LOW); //使直流电机（右）顺时针转
  digitalWrite(mPinIn1, HIGH);
  analogWrite(mPinEnB, int(B_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn3, HIGH); //使直流电机（左）逆时针转
  digitalWrite(mPinIn4, LOW);

  Serial.println("TurnRight");
  
  millis = START_DELAY_MS;
  millis += degree * STEP_1DEGREE_MS;

  return millis;
}


int CJCar::TurnLeft(int degree)//左转
{
  int millis = 0;
    
  analogWrite(mPinEnA, int(A_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn1, LOW); //使直流电机（右）顺时针转
  digitalWrite(mPinIn2, HIGH);
  analogWrite(mPinEnB, int(B_SPEED * gear)); //输入模拟值进行设定速度
  digitalWrite(mPinIn4, HIGH); //使直流电机（左）逆时针转
  digitalWrite(mPinIn3, LOW);

  Serial.println("TurnLeft");

  millis = START_DELAY_MS;
  millis += degree * STEP_1DEGREE_MS;

  return millis;
}
