#include "Vec2L.h"


Vec2::Vec2()
{
   x = 0;
   y = 0;
}

void Vec2::Normalize()
{
    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
        return;

    n = sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;

    n = 1.0f / n;
    x *= n;
    y *= n;
}

void Vec2::Sub(const Vec2& v1, const Vec2& v2, Vec2* dst)
{
    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
}

float Vec2::getAngle(const Vec2& p1,const Vec2& p2) const
{
    float angle = atan2f(p2.cross(p1), p2.dot(p1));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}
