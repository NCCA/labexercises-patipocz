#include <gtest/gtest.h>
#include"Particle.h"
#include "Vec3.h"
#include "Emitter.h"
TEST(Particle,ctor)
{
  Particle p;
  ASSERT_FLOAT_EQ(p.pos.x,0.0f);
  ASSERT_FLOAT_EQ(p.pos.y,0.0f);
  ASSERT_FLOAT_EQ(p.pos.z,0.0f);
  ASSERT_FLOAT_EQ(p.dir.x,0.0f);
  ASSERT_FLOAT_EQ(p.dir.y,0.0f);
  ASSERT_FLOAT_EQ(p.dir.z,0.0f);
  ASSERT_FLOAT_EQ(p.colour.x,0.0f);
  ASSERT_FLOAT_EQ(p.colour.y,0.0f);
  ASSERT_FLOAT_EQ(p.colour.z,0.0f);
  ASSERT_EQ(p.life , 0);
  ASSERT_EQ(p.size ,1.0f);

}

TEST(Particle,userCtor)
{
  Particle p({1,2,3},{0,1.0f,0},{1,1,1},100,2.0f);
  ASSERT_FLOAT_EQ(p.pos.x,1.0f);
  ASSERT_FLOAT_EQ(p.pos.y,2.0f);
  ASSERT_FLOAT_EQ(p.pos.z,3.0f);
  ASSERT_FLOAT_EQ(p.dir.x,0.0f);
  ASSERT_FLOAT_EQ(p.dir.y,1.0f);
  ASSERT_FLOAT_EQ(p.dir.z,0.0f);
  ASSERT_FLOAT_EQ(p.colour.x,1.0f);
  ASSERT_FLOAT_EQ(p.colour.y,1.0f);
  ASSERT_FLOAT_EQ(p.colour.z,1.0f);
  ASSERT_EQ(p.life , 100);
  ASSERT_FLOAT_EQ(p.size ,2.0f);
}

TEST(Vec3, ctor)
{
  Vec3 v;
  ASSERT_TRUE(v.x==0.0f);
  ASSERT_TRUE(v.y==0.0f);
  ASSERT_TRUE(v.z==0.0f);
}

TEST(Vec3,userCtor)
{
  Vec3 v(1.0f,2.0f,3.0f);
  ASSERT_TRUE(v.x==1.0f);
  ASSERT_TRUE(v.y==2.0f);
  ASSERT_TRUE(v.z==3.0f);
}

TEST(Emitter, ctor)
{
  Emitter e;
  ASSERT_EQ(e.numParticles(),0);
}