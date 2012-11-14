#include <cstdio>
#include <vector>

#include "physics.hpp"

const float Physics::timeStep = 1.0f / 60.0f;

Physics::Physics(float width, float height): m_width(width), m_height(height), m_world(b2Vec2(0.0f, 0.0f))
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.position.Set(0, 0);

  b2Body* boundaries = m_world.CreateBody(&bodyDef);

  b2PolygonShape shape;
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;

  shape.SetAsBox(width / 2.0f, 10.0f, Vector(width / 2.0f, -10.0f), 0);
  boundaries->CreateFixture(&fixtureDef);
  shape.SetAsBox(width / 2.0f, 10.0f, Vector(width / 2.0f, height + 10.0f), 0);
  boundaries->CreateFixture(&fixtureDef);
  shape.SetAsBox(10.0f, height / 2.0f, Vector(width + 10.0f, height / 2.0f), 0);
  boundaries->CreateFixture(&fixtureDef);
  shape.SetAsBox(10.0f, height / 2.0f, Vector(-10.0f, height / 2.0f), 0);
  boundaries->CreateFixture(&fixtureDef);
}

Physics::~Physics()
{
}

b2Body* Physics::addBox(Vector center, int width, int height)
{
  b2Body* body(createBody(center));

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(width / 2.0f, height / 2.0f);

  setFixture(body, &dynamicBox);

  return body;
}

b2Body* Physics::addPolygon(Vector center, const Polygon& points)
{
  b2Body* body(createBody(center));

  b2PolygonShape polygon;
  polygon.Set(&points[0], points.size());

  setFixture(body, &polygon);

  return body;
}

b2Body* Physics::addComplexPolygon(Vector center, const PolygonList& polygons)
{
  b2Body* body(createBody(center));

  b2PolygonShape shape;
  for (const auto& polygon: polygons)
  {
    shape.Set(&polygon[0], polygon.size());
    setFixture(body, &shape);
  }

  return body;
}

b2Body* Physics::createBody(Vector center)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = center;

  return m_world.CreateBody(&bodyDef);
}

void Physics::setFixture(b2Body* body, b2Shape* shape)
{
  b2FixtureDef fixtureDef;
  fixtureDef.shape = shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  body->CreateFixture(&fixtureDef);
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

