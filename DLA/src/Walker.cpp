#include "Walker.h"

#include <random>

std::random_device g_rd;
std::seed_seq g_seed{g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd()};
std::mt19937 g_rng(g_seed);
std::uniform_int_distribution<>g_walkDir(-1,1);


Walker::Walker(size_t _w, size_t _h)
{
    m_map=std::make_unique<Image> (_w,_h,255,255,255,0);
    initRNG();
}

void Walker::setImageSeed(size_t _x, size_t _y)
{
    m_map->setPixel(_x,_y,255,0,0,255);
}

void Walker::saveImage(const std::string &_fname) const
{
    m_map->write(_fname);
}

void Walker::randomImageSeed()
{
    m_map->setPixel(m_xRand(g_rng),m_yRand(g_rng),255,0,0,255);
}
void Walker::initRNG()
{
    m_xRand=std::uniform_int_distribution<>(1,m_map->width()-1);
    m_yRand=std::uniform_int_distribution<>(1,m_map->height()-1);

}

bool Walker::walk()
{
    return true;
}
void Walker::resetStart()
{
    m_xpos=m_xRand(g_rng);
    m_ypos=m_yRand(g_rng);
    std::cout<<"New Start "<<m_xpos<<' '<<m_ypos<<'\n';
}