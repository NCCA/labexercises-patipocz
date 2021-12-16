#ifndef VEC3_H_
#define VEC3_H_

struct Vec3
{

    Vec3()=default;
    Vec3(const Vec3 &)=default;
    Vec3 (float _x, float _y, float _z) : 
    x{_x}, y{_y}, z{_z}{}

    Vec3 operator *(const Vec3 &_rhs)const;
    Vec3 operator +(const Vec3 &_rhs)const;
    Vec3 operator *(float _rhs)const;
    void operator +=(const Vec3 &_rhs);

    float x=0.0f;
    float y=0.0f;
    float z=0.0f;
};

#endif