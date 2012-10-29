#include <cstring>

#include "graphics.hpp"
#include "color.hpp"
#include "drawfunctions.hpp"

Graphics::Graphics(int width, int height) : m_screen(SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                                          , m_buffer( SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32,
                                                      Color::RED_MASK, Color::BLUE_MASK, Color::GREEN_MASK, 0x00000000))
                                          , m_actualColor(Color::BLACK)
{
  clearBuffer();
}

Color::Pixel Graphics::setColor(Color::Pixel color)
{
  Color::Pixel old = m_actualColor;
  m_actualColor = color;
  return old;
}

void Graphics::show()
{
  SDL_BlitSurface(m_buffer, 0, m_screen, 0);
  SDL_Flip(m_screen);
  
  clearBuffer();
}

void Graphics::drawCircle(int x, int y, int radius, Color::Pixel color)
{
  DrawFunctions::drawCircle(x, y, radius, *m_buffer, color);
}


void Graphics::clearBuffer()
{
  std::memset(m_buffer->pixels, 0xff, m_buffer->w * m_buffer->h * (32 / 8));
}
