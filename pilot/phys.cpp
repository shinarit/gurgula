#include <cstdio>

#include <Box2D/Box2D.h>

int main()
{
  b2World world(b2Vec2(0.0f, -10.0f));
  
  //creating the ground
  b2BodyDef bodyDef;
  bodyDef.position.Set(0.0f, -10.0f);
  b2Body* groundBody(world.CreateBody(&bodyDef));
  
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
  
  //creating some other stuff
  bodyDef.type = b2_dynamicBody; 
  bodyDef.position.Set(0.0f, 4.0f); 
  b2Body* body = world.CreateBody(&bodyDef);
  bodyDef.position.Set(1.2f, 7.0f); 
  b2Body* body2 = world.CreateBody(&bodyDef);
  
  b2PolygonShape dynamicBox; 
  dynamicBox.SetAsBox(1.0f, 1.0f); 
  
  b2FixtureDef fixtureDef; 
  fixtureDef.shape = &dynamicBox; 
  fixtureDef.density = 1.0f; 
  fixtureDef.friction = 0.3f; 
  body->CreateFixture(&fixtureDef);
  body2->CreateFixture(&fixtureDef);
  
  //movement
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6; 
  int32 positionIterations = 2;
  for (int i(0); i < 100; ++i)
  {
    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition(); 
    float32 angle = body->GetAngle(); 
    b2Vec2 position2 = body2->GetPosition(); 
    float32 angle2 = body2->GetAngle(); 
    std::printf("%4.2f %4.2f %4.2f\n%4.2f %4.2f %4.2f\n\n", position.x, position.y, angle, position2.x, position2.y, angle2);
  }
}
