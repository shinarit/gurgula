#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "printer.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "flyer.hpp"
#include "framework.hpp"
#include "event_server.hpp"
#include "accessory/rocket_engine.hpp"

#include "SDL/SDL.h"

const int TIMER_EVENT = 0;
const int TIMER_INTERVAL = 20;
const int TIMER_RETRY_INTERVAL = 10;
const int NUM_OF_CIRCLES = 30;

const int width = 800;
const int height = 800;
const int physWidth = 40;
const int physHeight = height / 20;

const Vector EngineForce(40.0f, 0.0f);

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
  angle /= 3.0f;
  return Color::Color(std::sin(angle) * 64 + 64, std::cos(angle) * 64 + 64, std::sin(angle - 3.14f) * 64 + 64);
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
    b2Fixture* fixture = box->GetFixtureList();
    while (nullptr != fixture)
    {
      auto shape = reinterpret_cast<b2PolygonShape*>(fixture->GetShape());
      Polygon polygon(&shape->m_vertices[0], &shape->m_vertices[shape->m_vertexCount]);
      for (auto& vertex: polygon)
      {
        vertex = rotate(vertex, box->GetAngle());
        vertex = distort(vertex, physWidth, physHeight, width, height);
        vertex += distort(box->GetPosition(), physWidth, physHeight, width, height);
      }
      graphics.drawPolygon(polygon, colorFromAngle(box->GetAngle()));

      fixture = fixture->GetNext();
    }
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

Polygon readSubpolygon(const std::string& line)
{
  Polygon polygon;

  std::istringstream in(line);
  float x;
  float y;

  while (in >> x >> y)
  {
    polygon.push_back(Vector(x, y));
  }

  return polygon;
}

std::vector<Polygon> readPolygon(const std::string& file)
{
  std::vector<Polygon> res;

  std::ifstream in(file.c_str());
  std::string str;

  while (std::getline(in, str))
  {
    res.push_back(readSubpolygon(str));
  }

  return res;
}

struct E
{
  static const EventType eventType;
  typedef int Filter;
};

const EventType E::eventType = EventType::LAST_ELEMENT;

void f(const E&)
{}

int main(int argc, char* argv[])
{
  EventServer eventServer;
  eventServer.addListener(0, std::unique_ptr<functors::VirtualFunctor<void, const E&>>(functors::createFromFreeFunction(f)));

  std::srand(std::time(0));

  RaiiSdlMain sdlMain;
  
  Framework framework;
  
  Graphics graphics(width, height);

  Physics physics(physWidth, physHeight);

  std::vector<Circle> circles;
  std::vector<b2Body*> boxes;
  std::vector<Flyer> flyers;
  for (int i(0); i<NUM_OF_CIRCLES; ++i)
  {
    int r = std::rand() % 50 + 30;
    int x = width / 2;
    int y = height / 4;

    //circles.push_back(Circle{x, y, r, std::rand() % 30 - 15, std::rand() % 30 - 15, (std::rand() % 0xffffff) << 8});

    boxes.push_back(physics.addBox(Vector(physWidth / 2 + std::rand() % physWidth / 2 - physWidth / 4, physHeight / 2 + std::rand() % physHeight / 2 - physHeight / 4), 1, 1));
    boxes.back()->ApplyForceToCenter(Vector(std::rand() % 1000 - 500, std::rand() % 1000 - 500));
  }

  for (int i(1); i < argc; ++i)
  {
    boxes.push_back(physics.addComplexPolygon(Vector(physWidth / 2 + std::rand() % physWidth / 2 - physWidth / 4, physHeight / 2 + std::rand() % physHeight / 2 - physHeight / 4), readPolygon(argv[i])));
    flyers.push_back(std::move(Flyer(boxes.back())));
    boxes.back()->SetUserData(&flyers.back());
    flyers.back().addAccessory(Flyer::AccessoryRef(new RocketEngine(Vector(0, 0), Direction(), flyers.back(), framework)));
    for (const auto& acc: flyers.back().getAccessories())
    {
      //KeyCode code, const Controls::ControlEntity& control
      framework.addBinding(SDLK_a, acc->getControls()[0]);
    }
  }

  SDL_AddTimer(TIMER_INTERVAL, timerTick, 0);

  bool exit(false);
  bool forwardEngine(false);
  bool turnEngine(false);

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
        if (forwardEngine)
        {
          //boxes.back()->ApplyForceToCenter(rotate(EngineForce, boxes.back()->GetAngle()));
          boxes.back()->ApplyForce(EngineForce, boxes.back()->GetPosition() + rotate(Vector(1.5f, 0.5f), boxes.back()->GetAngle()));
        }
        if (turnEngine)
        {
          boxes.back()->ApplyTorque(1.0f);
        }
        ScopedPrinter printer("case SDL_USEREVENT:");
        draw(graphics, circles, boxes);
        graphics.show();
        move(boxes);
        physics.step();

        timerEventInQueue = false;

        break;
      }
      case SDL_KEYDOWN:
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
          {
            forwardEngine = true;

            break;
          }
          case SDLK_LEFT:
          {
            turnEngine = true;

            break;
          }
          default: break;
        }

        break;
      }
      case SDL_KEYUP:
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
          {
            forwardEngine = false;

            break;
          }
          case SDLK_LEFT:
          {
            turnEngine = false;

            break;
          }
          default: break;
        }

        break;
      }
    }
  }
}
