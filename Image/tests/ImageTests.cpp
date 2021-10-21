#include "Image.h"
#include <gtest/gtest.h>

TEST(RGBA, ctor)
{
    RGBA a;
    ASSERT_EQ(a.r, 0);
    ASSERT_EQ(a.g, 0);
    ASSERT_EQ(a.b, 0);
    ASSERT_EQ(a.a, 255);
}

TEST(RGBA,usr_ctor)
{
    RGBA a(255,128,64,55);
    ASSERT_EQ(a.r,255);
    ASSERT_EQ(a.g,128);
    ASSERT_EQ(a.b,64);
    ASSERT_EQ(a.a,55);
}

TEST(IMAGE, ctor)
{
    Image img;
    ASSERT_EQ(img.width(), 0);
    ASSERT_EQ(img.height(), 0);
}

TEST(IMAGE,userCtor)
{
    Image img(50,50);
}