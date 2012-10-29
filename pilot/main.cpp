#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "printer.hpp"
#include "drawfunctions.hpp"
#include "raiibaseclass.hpp"

#include "SDL/SDL.h"

typedef std::pair<SDL_Surface*, SDL_Surface*> ScreenBufferPair;

const int TIMER_EVENT = 0;

Uint32 timerTick(Uint32 interval, void* param)
{
  ScopedPrinter printer("Uint32 timerTick(Uint32 interval, void* param)");
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = TIMER_EVENT;
  SDL_PushEvent(&event);

  return interval;
}

struct RaiiSurface: CustomDeleteRaii<SDL_Surface>
{
  RaiiSurface(SDL_Surface* surface): CustomDeleteRaii(surface, SDL_FreeSurface)
  { }
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

int main(int argc, char* argv[])
{
  const int width = 600;
  const int height = 600;

  std::srand(std::time(0));

  SDL_Init( SDL_INIT_EVERYTHING );

  {
    ScopedPrinter printer("SDL_Init( SDL_INIT_EVERYTHING );");
    RaiiSurface screen(SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF));
    RaiiSurface buffer(SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32,
                                            0xff000000, 0x00ff0000, 0x0000ff00, 0x00000000));  //rgba masks

    
    const int NUM_OF_CIRCLES = 300;
    std::vector<Circle> circles;
    for (int i(0); i<NUM_OF_CIRCLES; ++i)
    {
      int r = std::rand() % 50 + 30;
      int x = width / 2;
      int y = height / 4;

      circles.push_back(Circle{x, y, r, std::rand() % 30 - 15, std::rand() % 30 - 15, (std::rand() % 0xffffff) << 8});
    }

    SDL_AddTimer(20, timerTick, 0);

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
          std::memset(buffer->pixels, 0xff, buffer->w * buffer->h * (32 / 8));

          for (auto& circle: circles)
          {
            ScopedPrinter printer("for (auto& circle: circles)");
            drawCircle(circle.x, circle.y, circle.r, *buffer, circle.color);
            circle.move(buffer->w, buffer->h);
          }

          SDL_BlitSurface(buffer, 0, screen, 0);
          SDL_Flip(screen);
        }
      }
    }
  }

  SDL_Quit();
}
