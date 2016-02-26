/*
  gp2y0a02红外测距模块控制类
 
 */
#ifndef CJUltraredSensor_H  //预编译指令，防止重复定义类
#define CJUltraredSensor_H

class CJUltraredSensor
{
private:
  int mPin;
  
public:
  CJUltraredSensor(int pin);//类的构造函数，与类名相同
  uint16_t GetDistance () ;

};

#endif // CJUltraredSensor_H
