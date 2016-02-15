/*
  小车控制类
 
 */
#ifndef CJCAR_H  //预编译指令，防止重复定义类
#define CJCAR_H

class CJCar
{
private:
  int mMode;
  float gear;
  
public:
  CJCar();//类的构造函数，与类名相同
  void MoveForward();
  void MoveBackward();
  void Stop();
  void TurnRight();
  void TurnLeft();
  void ChangeGear( float val );

};

#endif // CJCAR_H
