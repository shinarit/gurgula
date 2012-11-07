#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "basic_elements.hpp"

#include <Box2D/Box2D.h>

class Physics
{
  public:
    static const float Width;
    static const float Height;

    //creates a box from 0, 0 (topleft corner) to width - 1, height - 1 (botright corner), with gravity down
    Physics(float width, float height);
    ~Physics();

    b2Body* addBox(Vector center, int width, int height);
    void print(b2Body* body);
    void step();
    float getWidth();
    float getHeight();

  private:
    static const int velocityIterations = 8;
    static const int positionIterations = 2;
    static const float timeStep;

    const float m_width;
    const float m_height;
    b2World m_world;
};

#endif
