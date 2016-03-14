/*
  步进电机控制类
 
 */
#ifndef CJSTEPMOTOR_H  //预编译指令，防止重复定义类
#define CJSTEPMOTOR_H

//  int dirPin1 = 3;
//  int stepperPin1 = 2;
//  int dirPin2 = 7;
//  int stepperPin2 = 6;

class CJStepMotor
{
private:
  int mPinDir, mPinStep;
  bool mLastDir;

public:
  CJStepMotor(int direction_pin, int step_pin);//类的构造函数，与类名相同
  void StepOnce(bool direction);
  void Step(bool direction, int steps);
};

#endif // CJSTEPMOTOR_H