/*
  Debug类
 
 */
#ifndef CJDEBUGGER_H  //预编译指令，防止重复定义类
#define CJDEBUGGER_H

#include <SoftwareSerial.h>

#define DEBUG_PORT_NONE        0
#define DEBUG_PORT_SERIAL      1
#define DEBUG_PORT_BLUETOOTH   2

class CJDebugger
{
protected:
  static int mPort;
  static SoftwareSerial *mBTserial;
  static bool mEnableLog;
  
public:
  CJDebugger();//类的构造函数，与类名相同
  static void setup(int port, long baurate);
  static void println(String str);
  static SoftwareSerial *GetBtserial();
  static void EnableLog(bool bFlag);

};

#endif // CJDEBUGGER_H
