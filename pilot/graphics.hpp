#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "SDL/SDL.h"

#include "raiibaseclass.hpp"
#include "color.hpp"

struct RaiiSurface: CustomDeleteRaii<SDL_Surface>
{
  RaiiSurface(SDL_Surface* surface): CustomDeleteRaii(surface, SDL_FreeSurface)
  { }
};

class Graphics
{
  public:
    Graphics(int width, int height);
    
    Color::Pixel setColor(Color::Pixel color);
    void show();

    void drawCircle(int x, int y, int radius, Color::Pixel color);
    void drawCircle(int x, int y, int radius)
    {
      drawCircle(x, y, radius, m_actualColor);
    }
    
  private:
    void clearBuffer();
  
    RaiiSurface m_screen;
    RaiiSurface m_buffer;
    Color::Pixel m_actualColor;
};

#endif
