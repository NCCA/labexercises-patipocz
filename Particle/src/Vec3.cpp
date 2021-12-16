#include "Vec3.h"

    Vec3 Vec3::operator *(const Vec3 &_rhs) const
    {
        return Vec3(x*_rhs.x,y*_rhs.y,z*_rhs.z);
    }
    Vec3 Vec3::operator +(const Vec3 &_rhs) const
    {
        return Vec3(x+_rhs.x,y+_rhs.y,z+_rhs.z);
    }
    Vec3 Vec3::operator *(float _rhs) const
    {
        return Vec3(x*_rhs,y*_rhs,z*_rhs);
    }

    void Vec3::operator += (const Vec3 &_rhs)
    {
        x+=_rhs.x;
        y+=_rhs.y;
        z+=_rhs.z;
    }