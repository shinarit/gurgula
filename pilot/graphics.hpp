#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "SDL/SDL.h"

#include "basic_elements.hpp"
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
    //angle is CW, 0 is the x axis
    void drawBox(Vector center, int width, int height, float angle, Color::Pixel color);
    void drawBox(Vector center, int width, int height, float angle)
    {
      drawBox(center, width, height, angle, m_actualColor);
    }
    
  private:
    void clearBuffer();
  
    RaiiSurface m_screen;
    RaiiSurface m_buffer;
    Color::Pixel m_actualColor;
};

#endif
