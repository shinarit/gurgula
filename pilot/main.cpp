#include <cmath>
#include <cstdint>
#include <cstring>
#include <utility>

#include "SDL/SDL.h"

typedef uint32_t Pixel;

const int INSIDE  = 0;
const int LEFT    = 1;
const int RIGHT   = 2;
const int BOTTOM  = 4;
const int TOP     = 8;

int codeOfPoint(int x, int y, int width, int height)
{
  int flag = INSIDE;
  if (x < 0)
  {
    flag |= LEFT;
  }
  else if (x >= width)
  {
    flag |= RIGHT;
  }
  if (y < 0)
  {
    flag |= BOTTOM;
  }
  else if (y >= height)
  {
    flag |= TOP;
  }

  return flag;
}

//
// cohen-sutherland algorithm for clipping the line into the surface
// modifies its {x, y}{1, 2} parameters until they are clipped, or
// returns if the line should be drawn
//
bool cohenSutherland(int& x1, int& y1, int& x2, int& y2, int width, int height)
{
  int flag1(codeOfPoint(x1, y1, width, height));
  int flag2(codeOfPoint(x2, y2, width, height));

  if (INSIDE != (flag1 & flag2))
  {
    return false;
  }
  int both = flag1 | flag2;
  if (INSIDE == both)
  {
    return true;
  }

  if (both & TOP)
  {
    int x = x1 + (x2 - x1) * (height - 1 - y1) / (y2 - y1);
    int y = height - 1;
    int& xMod((y1 >= height) ? x1 : x2);
    int& yMod((y1 >= height) ? y1 : y2);
    xMod = x;
    yMod = y;
  }
  if (y1 < 0 || y2 < 0)
  {
    int x = x1 + (x2 - x1) * (0 - y1) / (y2 - y1);
    int y = 0;
    int& xMod((y1 < 0) ? x1 : x2);
    int& yMod((y1 < 0) ? y1 : y2);
    xMod = x;
    yMod = y;
  }
  if (x1 >= width || x2 >= width)
  {
    int x = width - 1;
    int y = y1 + (y2 - y1) * (width - 1 - x1) / (x2 - x1);
    int& xMod((x1 >= width) ? x1 : x2);
    int& yMod((x1 >= width) ? y1 : y2);
    xMod = x;
    yMod = y;
  }
  if (x1 < 0 || x2 < 0)
  {
    int x = 0;
    int y = y1 + (y2 - y1) * (0 - x1) / (x2 - x1);
    int& xMod((x1 < 0) ? x1 : x2);
    int& yMod((x1 < 0) ? y1 : y2);
    xMod = x;
    yMod = y;
  }

  flag1 = codeOfPoint(x1, y1, width, height);
  flag2 = codeOfPoint(x2, y2, width, height);
  if (flag1 | flag2)
  {
    return false;
  }
  return true;
}

Pixel* addressOf(int x, int y, SDL_Surface& surface)
{
  return static_cast<Pixel*>(surface.pixels) + x + y * surface.w;
}

//
// standard Bresenham's line algorithm binded to SDL by using surface
// accessing directly the canvas
// using Cohen-Sutherland clipping with binded 0,0 topleft corner of clip area
//
void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface, Pixel color = 0)
{
  if (!cohenSutherland(x1, y1, x2, y2, surface.w, surface.h))
  {
    return;
  }

  SDL_LockSurface(&surface);

  int dx = std::abs(x1 - x2);
  int dy = std::abs(y1 - y2);

  int sx = ((x1 < x2) ? 1 : -1);
  int sy = ((y1 < y2) ? 1 : -1);

  int err = dx - dy;

  Pixel* currPixel = addressOf(x1, y1, surface);
  const Pixel* destPixel = addressOf(x2, y2, surface);

  while (destPixel != currPixel)
  {
    *currPixel = color;

    int err2 = 2 * err;
    if (err2 > -dy)
    {
      err -= dy;
      currPixel += sx;
    }
    if (err2 < dx)
    {
      err += dx;
      currPixel += sy * surface.w;
    }
  }

  SDL_UnlockSurface(&surface);
}

//
// standard midpoint circle algorithm binded to SDL by using surface
// optimized by not using setPixel-like method, but access the canvas directly
//
void drawCircle(int x0, int y0, int radius, SDL_Surface& surface, Pixel color = 0)
{
  SDL_LockSurface(&surface);

  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  bool x0In = x0 >= 0 && x0 < surface.w;
  bool x0PRadIn = x0 + radius >= 0 && x0 + radius < surface.w;
  bool x0MRadIn = x0 - radius >= 0 && x0 - radius < surface.w;
  bool y0In = y0 >= 0 && y0 < surface.h;
  bool y0PRadIn = y0 + radius >= 0 && y0 + radius < surface.h;
  bool y0MRadIn = y0 - radius >= 0 && y0 - radius < surface.h;

  if (x0In)
  {
    if (y0PRadIn)
    {
      *addressOf(x0, y0 + radius, surface) = color;
    }
    if (y0MRadIn)
    {
      *addressOf(x0, y0 - radius, surface) = color;
    }
  }
  if (y0In)
  {
    if (x0PRadIn)
    {
      *addressOf(x0 + radius, y0, surface) = color;
    }
    if (x0MRadIn)
    {
      *addressOf(x0 - radius, y0, surface) = color;
    }
  }

  Pixel* northWest = addressOf(x0, y0 - radius, surface);
  Pixel* northEast = northWest;
  Pixel* eastNorth = addressOf(x0 + radius, y0, surface);
  Pixel* eastSouth = eastNorth;
  Pixel* southWest = addressOf(x0, y0 + radius, surface);
  Pixel* southEast = southWest;
  Pixel* westNorth = addressOf(x0 - radius, y0, surface);
  Pixel* westSouth = westNorth;

  while (x < y)
  {
    //{x, y}0 {Plus, Minus} {x, y} In
    bool x0PXIn = x0 + x < surface.w && x0 + x >= 0;
    bool x0MXIn = x0 - x < surface.w && x0 - x >= 0;
    bool x0PYIn = x0 + y < surface.w && x0 + y >= 0;
    bool x0MYIn = x0 - y < surface.w && x0 - y >= 0;
    bool y0PXIn = y0 + x < surface.h && y0 + x >= 0;
    bool y0MXIn = y0 - x < surface.h && y0 - x >= 0;
    bool y0PYIn = y0 + y < surface.h && y0 + y >= 0;
    bool y0MYIn = y0 - y < surface.h && y0 - y >= 0;

    if (f >= 0)
    {
      --y;
      ddF_y += 2;
      f += ddF_y;

      northWest += surface.w;
      northEast += surface.w;
      --eastNorth;
      --eastSouth;
      southEast -= surface.w;
      southWest -= surface.w;
      ++westNorth;
      ++westSouth;
    }
    ++x;

    --northWest;
    ++northEast;
    eastNorth -= surface.w;
    eastSouth += surface.w;
    --southWest;
    ++southEast;
    westNorth -= surface.w;
    westSouth += surface.w;

    ddF_x += 2;
    f += ddF_x;

    if (y0MYIn && x0MXIn)
    {
      *northWest = color;
    }
    if (y0MYIn && x0PXIn)
    {
      *northEast = color;
    }
    if (x0PYIn && y0MXIn)
    {
      *eastNorth = color;
    }
    if (x0PYIn && y0PXIn)
    {
      *eastSouth = color;
    }
    if (y0PYIn && x0MXIn)
    {
      *southWest = color;
    }
    if (y0PYIn && x0PXIn)
    {
      *southEast = color;
    }
    if (x0MYIn && y0MXIn)
    {
      *westNorth = color;
    }
    if (x0MYIn && y0PXIn)
    {
      *westSouth = color;
    }
  }

  SDL_UnlockSurface(&surface);
}

typedef std::pair<SDL_Surface*, SDL_Surface*> ScreenBufferPair;

Uint32 draw(Uint32 interval, void* param)
{
  static int i(0);

  ScreenBufferPair* sbp(static_cast<ScreenBufferPair*>(param));

  SDL_Surface& screen(*sbp->first);
  SDL_Surface& buffer(*sbp->second);

  std::memset(buffer.pixels, 0xff, buffer.w * buffer.h * (32 / 8));

  drawLine(i * 2, 0, i * 2, buffer.h, buffer, 0x00ffff00);
  drawCircle(i, i * 2, i / 4, buffer);

  SDL_BlitSurface(&buffer, 0, &screen, 0);
  SDL_Flip(&screen);

  i = (i + 1) % 200;

  return interval;
}

template<class T>
struct SdlRaii
{
  typedef T* Tptr;
  typedef void (*FreeFunction)(Tptr);
  SdlRaii(T* ptr, FreeFunction free): m_ptr(ptr), m_free(free)
  { }
  ~SdlRaii()
  {
    m_free(m_ptr);
  }
  operator Tptr()
  {
    return m_ptr;
  }
  T*            m_ptr;
  FreeFunction  m_free;
};

struct RaiiSurface: SdlRaii<SDL_Surface>
{
  RaiiSurface(SDL_Surface* surface): SdlRaii(surface, SDL_FreeSurface)
  { }
};

int main(int argc, char* argv[])
{
  const int width = 300;
  const int height = 300;

  SDL_Init( SDL_INIT_EVERYTHING );

  {
    RaiiSurface screen(SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF));
    RaiiSurface buffer(SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32,
                                            0xff000000, 0x00ff0000, 0x0000ff00, 0x00000000));  //rgba masks

    auto surfacePair = std::make_pair(static_cast<SDL_Surface*>(screen), static_cast<SDL_Surface*>(buffer));
    SDL_AddTimer(50, draw, &surfacePair);

    bool exit = false;

    SDL_Event event;
    while (!exit && 1 == SDL_WaitEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
        {
          exit = true;
          break;
        }
      }
    }
  }

  SDL_Quit();
}
