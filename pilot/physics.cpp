#include <cstdio>
#include <vector>

#include "physics.hpp"

const float Physics::timeStep = 1.0f / 60.0f;

Physics::Physics(float width, float height): m_width(width), m_height(height), m_world(b2Vec2(0.0f, 0.0f))
{
  //creating the boundaries
  b2PolygonShape horizontalBox;
  b2PolygonShape verticalBox;

  horizontalBox.SetAsBox(width / 2.0f, 10.0f);
  verticalBox.SetAsBox(10.0f, height / 2.0f);

  b2BodyDef bodyDef;

  //top and bottom
  bodyDef.position.Set(width / 2.0f, -10.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&horizontalBox, 0.0f);
  bodyDef.position.Set(width / 2.0f, height + 10.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&horizontalBox, 0.0f);

  //left and right
  bodyDef.position.Set(-10.0f, height / 2.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&verticalBox, 0.0f);
  bodyDef.position.Set(width + 10.0f, height / 2.0f);
  m_world.CreateBody(&bodyDef)->CreateFixture(&verticalBox, 0.0f);
}

Physics::~Physics()
{
}

b2Body* Physics::addBox(Vector center, int width, int height)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = center;
  b2Body* body(m_world.CreateBody(&bodyDef));

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(width / 2.0f, height / 2.0f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
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

float Physics::getWidth()
{
  return m_width;
}

float Physics::getHeight()
{
  return m_height;
}

