#include <cmath>
#include <cstdint>

#include "SDL/SDL.h"

typedef uint32_t Pixel;

void setPixel(int x, int y, SDL_Surface& surface, Pixel pixel = 0)  //0 should mean zero?
{
  SDL_LockSurface(&surface);

  Pixel* pixels = static_cast<Pixel*>(surface.pixels);
  pixels[y * surface.w + x] = pixel;

  SDL_UnlockSurface(&surface);
}

void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface)
{
  int dx = std::abs(x1 - x2);
  int dy = std::abs(y1 - y2);

  int sx = ((x1 < x2) ? 1 : -1);
  int sy = ((y1 < y2) ? 1 : -1);

  int err = dx - dy;

  while (true)
  {
    setPixel(x1, y1, surface);
    if (x1 == x2 && y1 == y2)
    {
      break;
    }
    int err2 = 2 * err;
    if (err2 > -dy)
    {
      err -= dy;
      x1 += sx;
    }
    if (err2 < dx)
    {
      err += dx;
      y1 += sy;
    }
  }
}

void drawCircle(int x0, int y0, int radius, SDL_Surface& surface)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  setPixel(x0, y0 + radius, surface);
  setPixel(x0, y0 - radius, surface);
  setPixel(x0 + radius, y0, surface);
  setPixel(x0 - radius, y0, surface);

  while(x < y)
  {
    if(f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    setPixel(x0 + x, y0 + y, surface);
    setPixel(x0 - x, y0 + y, surface);
    setPixel(x0 + x, y0 - y, surface);
    setPixel(x0 - x, y0 - y, surface);
    setPixel(x0 + y, y0 + x, surface);
    setPixel(x0 - y, y0 + x, surface);
    setPixel(x0 + y, y0 - x, surface);
    setPixel(x0 - y, y0 - x, surface);
  }
}

int main(int argc, char* argv[])
{
  SDL_Init( SDL_INIT_EVERYTHING );

  SDL_Surface* screen(SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE));
  SDL_Surface* pic(SDL_LoadBMP(argv[1]));

  for (int i(0); i<100; ++i)
  {
    //drawLine(i * 2, 0, i * 2, 200, *pic);
    drawCircle(i, i * 2, i, *pic);
  }

  SDL_BlitSurface(pic, 0, screen, 0);
  SDL_Flip(screen);

  SDL_Delay( 2000 );

  SDL_FreeSurface( pic );

  SDL_Quit();
}
