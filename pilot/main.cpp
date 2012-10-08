#include <cmath>
#include <cstdint>

#include "SDL/SDL.h"

typedef uint32_t Pixel;

Pixel* addressOf(int x, int y, SDL_Surface& surface)
{
  return static_cast<Pixel*>(surface.pixels) + x + y * surface.w;
}

void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface, Pixel color = 0)
{
  SDL_LockSurface(&surface);

  int dx = std::abs(x1 - x2);
  int dy = std::abs(y1 - y2);

  int sx = ((x1 < x2) ? 1 : -1);
  int sy = ((y1 < y2) ? 1 : -1);

  int err = dx - dy;

  const Pixel* lowerThreshold = addressOf(0, 0, surface);
  const Pixel* upperThreshold = addressOf(surface.w, surface.h, surface);

  Pixel* currPixel = addressOf(x1, y1, surface);
  const Pixel* destPixel = addressOf(x2, y2, surface);

  while (destPixel != currPixel && currPixel < upperThreshold && currPixel >= lowerThreshold)
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

int main(int argc, char* argv[])
{
  SDL_Init( SDL_INIT_EVERYTHING );

  SDL_Surface* screen(SDL_SetVideoMode(100, 100, 32, SDL_SWSURFACE));
  SDL_Surface* pic(SDL_LoadBMP(argv[1]));

  for (int i(0); i<100; ++i)
  {
    //drawLine(i * 2, 0, i * 2, 200, *pic);
    //drawCircle(i, i * 2, i, *pic);
  }
  drawCircle(65, 65, 1000, *pic);

  SDL_BlitSurface(pic, 0, screen, 0);
  SDL_Flip(screen);

  SDL_Delay( 2000 );

  SDL_FreeSurface( pic );

  SDL_Quit();
}
