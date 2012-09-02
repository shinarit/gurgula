#include "common.hpp"
#include "expect.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>

struct Circle
{
  Coordinate center;
  Color color;
  int size;

  int death;
};

std::vector<Circle> circles;

//
// playground :[0-1000]x[0-1000]
//

const int playgroundSize = 1000;


int Sqr(int n)
{
  return n*n;
}

int Distance(Coordinate lhs, Coordinate rhs)
{
  return Sqr(lhs.x - rhs.x) + Sqr(lhs.y - rhs.y);
}

Circle Create()
{
  return Circle{Coordinate(rand() % playgroundSize, rand() % playgroundSize),
                Color(rand() % 256, rand() % 256, rand() % 256),
                rand() % 40 + 5,
                0};
}

void Reinstall(Circle& obj)
{
  obj = Create();
}


void CheckCollision(Circle& obj)
{
  for(Circle& c: circles)
  {
    if (0 == c.death && Distance(c.center, obj.center) < c.size + obj.size && &c != &obj)
    {
      c.death = rand() % 20 + 1;
      obj.death = rand() % 20 + 1;
      return;
    }
  }
}


void InitPilot()
{
  std::srand(time(0));
  for(int i(0); i<500; ++i)
  {
    circles.push_back(Create());
  }
}

void DoPilot()
{
  for(Circle& c: circles)
  {
    if (c.death > 0)
    {
      if (0 == --c.death)
      {
        Reinstall(c);
      }
    }
    else
    {
      CheckCollision(c);
    }

    if (!c.death)
    {
      DrawCircle(c.center, c.size, c.color);
    }
  }
}

