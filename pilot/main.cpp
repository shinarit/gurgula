#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "printer.hpp"
#include "graphics.hpp"
#include "physics.hpp"

#include "SDL/SDL.h"

const int TIMER_EVENT = 0;
const int TIMER_INTERVAL = 20;
const int TIMER_RETRY_INTERVAL = 10;
const int width = 800;
const int height = 800;
const int physWidth = 8;
const int physHeight = height / 200;

struct RaiiSdlMain
{
  RaiiSdlMain()
  {
    SDL_Init(SDL_INIT_EVERYTHING);
  }
  ~RaiiSdlMain()
  {
    SDL_Quit();
  }
};

struct Circle
{
  static const int GRAVITY = 1;
  int x;
  int y;
  int r;
  int dx;
  int dy;
  int color;
  void move(int w, int h)
  {
    ScopedPrinter printer("void move(int w, int h)");

    x += dx;
    if (x + r >= w || x - r < 0)
    {
      dx = -dx;
      if (x + r >= w)
      {
        x = -(x + r - w) + w - r - 1;
      }
      else
      {
        x = -(x - r) + r;
      }
    }
    y += dy;
    if (y + r >= h || y - r < 0)
    {
      dy = -dy;
      if (y + r >= h)
      {
        y = -(y + r - h) + h - r - 1;
      }
      else
      {
        y = -(y - r) + r;
      }
    }
    dy += GRAVITY;
  }
};

Color::Pixel colorFromAngle(float angle)
{
  return Color::Color(int(angle*127) % 127, int(angle*127 + 100) % 127, int(angle*127 + 50) % 127);
}

void draw(Graphics& graphics, std::vector<Circle>& circles, std::vector<b2Body*>& boxes)
{
  for (auto& circle: circles)
  {
    ScopedPrinter printer("for (auto& circle: circles)");
    graphics.drawCircle(circle.x, circle.y, circle.r, circle.color);
    circle.move(width, height);
  }
  for (auto box: boxes)
  {
    /*auto shape = reinterpret_cast<b2PolygonShape*>(box->GetFixtureList()->GetShape());
    Polygon polygon(&shape->m_vertices[0], &shape->m_vertices[shape->m_vertexCount]);
    for (auto& vertex: polygon)
    {
      vertex *= float(width) / physWidth;
      vertex += (float(width) / physWidth) * box->GetPosition();
    }*/
    Vector center(box->GetPosition());
    graphics.drawBox(Vector((float(width) / physWidth) * center.x, float(height) / physHeight * center.y),
                     float(width) / physWidth, float(height) / physHeight, box->GetAngle()/*, colorFromAngle(box->GetAngle())*/);
  }
}

void move(std::vector<b2Body*>& boxes)
{
  for (int i(0); i < 20; ++i)
  {
    //boxes[std::rand() % boxes.size()]->ApplyTorque((std::rand() % 80 - 40) / 1.0f);
    //boxes[std::rand() % boxes.size()]->ApplyForceToCenter(Vector(std::rand() % 500 - 240, std::rand() % 500 - 240));
  }
}

bool timerEventInQueue(false);

Uint32 timerTick(Uint32 interval, void* param)
{
  if (!timerEventInQueue)
  {
    timerEventInQueue = true;
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = TIMER_EVENT;
    SDL_PushEvent(&event);

    return TIMER_INTERVAL;
  }
  else
  {
    return TIMER_RETRY_INTERVAL;
  }
}

int main(int argc, char* argv[])
{
  std::srand(std::time(0));

  RaiiSdlMain sdlMain;
  Graphics graphics(width, height);

  Physics physics(physWidth, physHeight);

  const int NUM_OF_CIRCLES = 3;
  std::vector<Circle> circles;
  std::vector<b2Body*> boxes;
  for (int i(0); i<NUM_OF_CIRCLES; ++i)
  {
    int r = std::rand() % 50 + 30;
    int x = width / 2;
    int y = height / 4;

    //circles.push_back(Circle{x, y, r, std::rand() % 30 - 15, std::rand() % 30 - 15, (std::rand() % 0xffffff) << 8});

    boxes.push_back(physics.addBox(Vector(physWidth / 2 + std::rand() % physWidth / 2 - physWidth / 4, physHeight / 2 + std::rand() % physHeight / 2 - physHeight / 4), 1, 1));
    boxes.back()->ApplyForceToCenter(Vector(std::rand() % 1000 - 500, std::rand() % 1000 - 500));
  }

  SDL_AddTimer(TIMER_INTERVAL, timerTick, 0);

  bool exit(false);

  SDL_Event event;
  while (!exit && 1 == SDL_WaitEvent(&event))
  {
    ScopedPrinter printer("while (!exit && 1 == SDL_WaitEvent(&event))");
    switch (event.type)
    {
      case SDL_QUIT:
      {
        exit = true;
        break;
      }
      case SDL_USEREVENT:
      {
        ScopedPrinter printer("case SDL_USEREVENT:");
        draw(graphics, circles, boxes);
        graphics.show();
        move(boxes);
        physics.step();

        timerEventInQueue = false;
      }
    }
  }
}
