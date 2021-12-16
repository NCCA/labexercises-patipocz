#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"

struct Particle
{
    
    Particle()=default;
    Particle(const Vec3 &_pos, const Vec3 &_dir,
    const Vec3 &_colour, int _life, float _size) :
    pos{_pos},dir{_dir},colour{_colour}, life{_life},size{_size}{}
    Vec3 pos;
    Vec3 dir;
    Vec3 colour;
    float size=0.01f;
    int life=0;
    int maxLife=10;
    
     
};

#endif