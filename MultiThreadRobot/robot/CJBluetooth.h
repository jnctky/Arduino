/*
  Bluetooth通信类
 
 */
#ifndef CJBLUETOOTH_H  //预编译指令，防止重复定义类
#define CJBLUETOOTH_H

#include <SoftwareSerial.h>

class CJBluetooth
{
private:
  SoftwareSerial *mBTserial;
  
public:
  CJBluetooth();//类的构造函数，与类名相同
  void setup(int rx, int tx, long baurate);
  void println(String str);
  SoftwareSerial *GetBtserial();

};

#endif // CJBLUETOOTH_H
