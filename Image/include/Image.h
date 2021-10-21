#ifndef TEST_H_
#define TEST_H_

#include <cstdint>
#include <cstdlib>


struct RGBA
{
    union
    {
        struct
        {
            unsigned char r=0;
            unsigned char g=0;
            unsigned char b=0;
            unsigned char a=255;
        };
        uint32_t pixels;
    };

    RGBA() = default;
    RGBA(   unsigned char _r,
            unsigned char _g, 
            unsigned char _b, 
            unsigned char _a)
            :
            r(_r),
            g(_g),
            b(_b),
            a(_a)
    {}
};

class Image
{
    public :
        size_t width() const;
        size_t height() const;
        
    private : 
        size_t m_width=0;
        size_t m_height=0;
};

#endif