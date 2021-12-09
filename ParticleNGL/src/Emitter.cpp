#include "Emitter.h"
#include<iostream>
#include "Random.h"
#include <fstream> //file stream
#include <sstream> //string stream 
#include <fmt/format.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include <ngl/VAOFactory.h>


Emitter::Emitter(size_t _numParticles, const ngl::Vec3 &_emitDir)
{
    m_emitDir=_emitDir;
    m_particles.resize(_numParticles);
    for(auto &p : m_particles)
    {
        resetParticle(p);
    }
    m_vao =ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}
void Emitter::resetParticle(Particle &io_p)
{
    if(Random::randomPositiveFloat(500)>450)
    {
        io_p.dir = m_emitDir * Random::randomPositiveFloat() + Random::randomVectorOnSphere() * m_spread;
        io_p.dir.m_y = std::abs(io_p.dir.m_y);
        io_p.colour = Random::randomPositiveVec3();
        io_p.maxLife = static_cast<int>(Random::randomPositiveFloat(5000)+100);
        io_p.life = 0;
        io_p.size = 0.01f;
    }
    else
    {
        io_p.dir.set(0.0f,0.0f,0.0f);
        io_p.pos.set(0.0f,-1.0f,0.0);
        io_p.maxLife=150;
        io_p.life=0;
    }
}
size_t Emitter::numParticles() const
{
    return m_particles.size();
}

void Emitter::update()
{
    
        /*
        dt = time step
    gravity=Vec3(0.0f, -9.81f, 0.0f)
    for each particle :
        dir += gravity * _dt * 0.5f
        pos += p.dir * _dt
        scale += randomPositiveFloat(0.05)
        life +=1
        if life >= maxLife or hit ground plane :
            resetParticle
    */

    float dt=0.1f;
    const ngl::Vec3 gravity(0.0f,-9.81f, 0.0f);
    for (auto &p : m_particles)   //whenever something is mutable we need a reference &
    {
        p.dir += gravity*dt*0.5f;
        p.pos += p.dir * dt;
        p.size += Random::randomPositiveFloat(0.5f);

        if(++p.life>= p.maxLife || p.pos.m_y<=0.0f)
        {
            resetParticle(p);
        }

    }
}
void Emitter::render() const
{
    auto view=ngl::lookAt({15,15,15},{0,0,0},{0,1,0});
    auto project=ngl::perspective(45.0f, 1.0f,0.1f,200.0f);
    ngl::ShaderLib::setUniform( "MVP",project*view);
    
    //ngl::ShaderLib::setUniform("colour",1.0f,0.0f,0.0f);
    //glPointSize(20);
    m_vao->bind();

    m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].pos.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);
    m_vao->setVertexAttributePointer(2,1,GL_FLOAT,sizeof(Particle),9);
    m_vao->setNumIndices(m_particles.size());
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);

    m_vao->draw();
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_MULTISAMPLE);

    m_vao->unbind();
    //ngl::Mat4 model;
    //for(auto p : m_particles)
    {
        //std::cout<<p.pos.m_x<<' '<<p.pos.m_y<<' '<<p.pos.m_z<<'\n';
        //std::cout<<p.dir.m_x<<' '<<p.dir.m_y<<' '<<p.dir.m_z<<'\n';
        //model.translate(p.pos.m_x, p.pos.m_y, p.pos.m_z);
        //ngl::ShaderLib::setUniform("MVP", project*view*model);
        //ngl::ShaderLib::setUniform("colour",p.colour.m_r,p.colour.m_g,p.colour.m_b);
        //ngl::VAOPrimitives::draw("sphere");
    }
}

void Emitter::saveFrame(int _frameNo) const
{
    //Houdini typpe complicated but supports points so yay
    std::ofstream file;  //ofstream is out file stream
    file.open(fmt::format("particle{:04d}.geo",_frameNo+1));
    std::stringstream ss; //quicker than straight into file
    ss << "PGEOMETRY V5\n";
    ss << "NPoints "<< m_particles.size() << " NPrims 1 \n";
    ss << "NPointGroups 0 NPrimGroups 0 \n";
    ss << "NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0 \n";
    ss << "PointAttrib \n";
    ss << "Cd 3 float 1 1 1 \n";
    ss << "pscale 1 float 1 \n";
    
    for(auto p : m_particles)
    {
        ss<<p.pos.m_x<<' '<<p.pos.m_y<<' '<<p.pos.m_z<<" 1 (";
        ss<<p.colour.m_x<<' '<<p.colour.m_y<<' '<<p.colour.m_z<<' ';
        ss<<p.size<<")\n";
    }
    ss<<"PrimitiveAttrib \n";
    ss<<"generator 1 index 1 papi \n";
    ss<<"Part "<<m_particles.size()<<' ';
    for(size_t i=0; i<m_particles.size();++i)
    {
        ss<<i<<' ';
    }
    ss<<"[0]\n";
    ss<<"beginExtra \n";
    ss<<"endExtra \n";


    file<<ss.rdbuf();
    file.close();  //every time you open file you need corresponding close

}