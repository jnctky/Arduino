
#ifndef Vec2_h
#define Vec2_h

class  Vec2
{

public:
    float x;

    float y;

    Vec2();

    inline float Dot(const Vec2L& p1)
    {
      return  x * p1.x + y * p1.y;
    }

    inline float cross(const Vec2& other)
    {
        return x*other.y - y*other.x;
    };

    void Normalize();

    static void Sub(const Vec2& v1, const Vec2& v2, Vec2* dst);

    static float getAngle(const Vec2& p1,const Vec2& p2) const;
}

#endif
