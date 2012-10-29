#include <cstdio>
#include <vector>

#include "physics.hpp"

Physics::Physics(): m_world(b2Vec2(0.0f, -10.0f))
{
  //creating the boundaries
  b2PolygonShape horizontalBox;
  b2PolygonShape verticalBox;

  //top and bottom
  horizontalBox.SetAsBox(Width / 2.0f, 10.0f);
  verticalBox.SetAsBox(10.0f, Height / 2.0f);

  b2BodyDef bodyDef;

  bodyDef.position.Set(0.0f, -10.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&horizontalBox, 0.0f);
  bodyDef.position.Set(0.0f, Height + 10.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&horizontalBox, 0.0f);

  bodyDef.position.Set(-Width / 2.0f - 10.0f, Height / 2.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&verticalBox, 0.0f);
  bodyDef.position.Set(Width / 2.0f + 10.0f, Height / 2.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&verticalBox, 0.0f);
}

Physics::~Physics()
{
}

b2Body* Physics::addBox(int x, int y, int w, int h)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody; 
  bodyDef.position.Set(x, y); 
  b2Body* body(m_world.CreateBody(&bodyDef));

  b2PolygonShape dynamicBox; 
  dynamicBox.SetAsBox(w / 2.0f, h / 2.0f); 
  
  b2FixtureDef fixtureDef; 
  fixtureDef.shape = &dynamicBox; 
  fixtureDef.density = 1.0f; 
  fixtureDef.friction = 0.3f; 
  body->CreateFixture(&fixtureDef);
  
  return body;
}

void Physics::print(b2Body* body)
{
  b2Vec2 position = body->GetPosition();
  float32 angle = body->GetAngle();
  std::printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}

void Physics::step()
{
  m_world.Step(timeStep, velocityIterations, positionIterations);
}

int main()
{
  Physics phys;
  b2Body* body(phys.addBox(0, 10, 1, 1));
  phys.print(body);
  for (int i(0); i < 300; ++i)
    phys.step();
  phys.print(body);
}
