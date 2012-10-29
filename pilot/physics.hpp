#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <Box2D/Box2D.h>

const float Width = 40.0f;
const float Height = 40.0f;
const int velocityIterations = 8;
const int positionIterations = 2;
const float timeStep = 1.0f / 60.0f;

class Physics
{
  public:
    Physics();
    ~Physics();
    
    b2Body* addBox(int x, int y, int w, int h);
    void print(b2Body* body);
    void step();
    
  private:
    b2World m_world;
    // b2Body* m_boundaries[4];
    // std::vector<b2Body*> m_movingStuff;
};

#endif
