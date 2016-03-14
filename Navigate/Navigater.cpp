#include "Navigater.h"


Navigater::Navigater()
{
  curPos    = new Vec2();
  prePos    = new Vec2();
  targetPos = new Vec2();


  curCount   = 0;
}

Navigater::~Navigater()
{
   delete curPos;
   delete prePos;
   delete targetPos;
}

void Navigater::SetTarget(long tx, long ty)
{
  targetPos->x = tx;
  targetPos->y = ty;
}

float Navigater::Excute(long x, long y)
{
  if(curCount == 0)
  {
    prePos->x = x;
    prePos->y = y;
  }

  curCount ++;

  if(curCount == SampleRate)
  {
    curPos->x = x;
    curPos->y = y;

    float rotate = CaculateRotate(&curPos,&prePos,&targetPos);

    prePos->x = curPos->x;
    prePos->y = curPos->y;

    curCount = 1;
  }
}

float Navigater::CaculateRotate(const Vec2& posA,
                                const Vec2& posB,
                                const Vec2& posC)
{
     Vec2* v1 = new Vec2();
     Vec2* v2 = new Vec2();

     Vec2.Sub(posA, posB, v1);
     Vec2.Sub(posC, posB, v2);

    v1.Normalize();
    v2.Normalize();

    float rotate = Vec2.GetAngle(&v1,&v2);

    return rotate;
}
