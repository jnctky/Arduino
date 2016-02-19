/*
  小车控制类
 
 */
#ifndef CJCAR_H  //预编译指令，防止重复定义类
#define CJCAR_H

class CJCar
{
private:
  int mMode;
  int mPinEnA, mPinIn1, mPinIn2, mPinEnB, mPinIn3, mPinIn4;
  float gear;
  
public:
  CJCar(int enA, int in1, int in2, int enB, int in3, int in4);//类的构造函数，与类名相同
  void MoveForward();
  void MoveBackward();
  void Stop();
  int TurnRight(int degree);
  int TurnLeft(int degree);
  void ChangeGear( float val );

};

#endif // CJCAR_H
