
#ifndef Navigater_h
#define Navigater_h

#define SampleRate 2;


#include "Vec2L.h"

class Navigater
{
private:
   Vec2* prePos;
   Vec2* targetPos;
   Vec2* curPos;

   int curCount;
public:
  Navigater();
  ~Navigater();
  float Excute(float x,float y);
  void SetTarget(float tx, float ty);

Private:
  float CaculateRotate();
}

#endif
