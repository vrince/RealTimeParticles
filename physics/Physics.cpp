
#include "Physics.hpp"

Core::Physics::Physics(int boxSize, int numEntities) : m_boxSize(boxSize), m_numEntities(numEntities){}

void* Core::Physics::getCoordsBufferStart()
{
    return &m_coordsBuffer[0];
}

void* Core::Physics::getColorsBufferStart()
{
    return &m_colorsBuffer[0];
}

void Core::Physics::update()
{
    updatePhysics();
    updateBuffers();
}

void Core::Physics::updateBuffers()
{
    if(m_numEntities > NUM_MAX_ENTITIES) return;

    for(int i = 0; i < m_numEntities; ++i) 
    {
        m_coordsBuffer[i] = { m_entities[i].xyz[0], m_entities[i].xyz[1], m_entities[i].xyz[2] } ;
        m_colorsBuffer[i] = { m_entities[i].rgb[0], m_entities[i].rgb[1], m_entities[i].rgb[2] };
    }
}

void Core::Physics::updateBoid(Entity &particle)
{
    if (!m_pause)
    {
        particle.vxyz += particle.axyz;

        if (Math::length(particle.vxyz) > m_maxVelocity || m_forcedmaxspeed)
        {
            particle.vxyz = normalize(particle.vxyz) * m_maxVelocity;
        }
        particle.xyz += particle.vxyz;
        particle.axyz = {0.0f, 0.0f, 0.0f};
    }
}

void Core::Physics::bouncingWall(Entity &particle)
{

    if (abs(particle.xyz[0]) > m_boxSize / 2)
    {
        particle.vxyz[0] = -particle.vxyz[0];
    }
    if (abs(particle.xyz[1]) > m_boxSize / 2)
    {
        particle.vxyz[1] = -particle.vxyz[1];
    }
    if (abs(particle.xyz[2]) > m_boxSize / 2)
    {
        particle.vxyz[2] = -particle.vxyz[2];
    }
}