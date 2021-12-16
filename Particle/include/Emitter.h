#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include <Particle.h>

class Emitter
{
    public :
    Emitter()=default;
    Emitter(size_t _numParticles, const Vec3 &_emitDir);
    void update();
    void render() const ;
    size_t numParticles() const ;
    void saveFrame(int _frameNo) const;

    private :
    void resetParticle(Particle &io_p);
    std::vector<Particle>m_particles;
    Vec3 m_emitDir={0.0f,40.0f,0.0f};
    float m_spread = 1.9f;
    


};

#endif