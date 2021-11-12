#include "Image.h"
#include <cstring>
#include <OpenImageIO/imageio.h>


Image::Image(size_t _w, size_t _h) : m_width{_w}, m_height{_h}
{
    m_pixels = std::make_unique<RGBA []>(m_width*m_height);
}


Image::Image(size_t _w, size_t _h, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : m_width{_w}, m_height{_h}
{
    m_pixels = std::make_unique<RGBA []>(m_width*m_height);
    RGBA p(_r,_g,_b,_a);
        for(size_t i=0; i<m_width*m_height; ++i)
            m_pixels[i]=p;
}
size_t Image::width() const
{
    return m_width;

}

size_t Image::height() const
{
    return m_height;

}

RGBA Image::getPixel(size_t _x, size_t _y)
{
    return m_pixels[_y*m_height + _x];
}

bool Image::write(const std::string &_frame) const
{


  bool success=true;

  using namespace OIIO;
  std::unique_ptr<ImageOutput> out = ImageOutput::create (_frame.data());
  if(!out)
  {
    return false;
  }
  ImageSpec spec (m_width,m_height,4, TypeDesc::UINT8);
  success=out->open(_frame.data(),spec);
  success=out->write_image(TypeDesc::UINT8,m_pixels.get());
  success=out->close();
  return success;
}

void Image::setPixel(size_t _x, size_t _y, RGBA _p)
{
    m_pixels[_y*m_width + _x] = _p;
}


void Image::setPixel(size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
    m_pixels[_y*m_width + _x] = RGBA(_r,_g,_b,_a);
}