/*
  超声波测距类
 
 */
#ifndef CJULTRASONICSENSOR_H  //预编译指令，防止重复定义类
#define CJULTRASONICSENSOR_H

class CJUltrasonicSensor
{
private:
  int mMode;
  int mInputPin;
  int mOutputPin;
  int GetDistanceMode1();
  int GetDistanceMode2();
  
public:
  CJUltrasonicSensor();
  CJUltrasonicSensor(int mode, int inputPin, int outputPin); //类的构造函数，与类名相同
  void setMode(int mode, int inputPin, int outputPin);
  int GetDistance();

};

#endif // CJULTRASONICSENSOR_H


