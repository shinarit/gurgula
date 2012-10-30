#include <cstring>

#include "printer.hpp"

#include "graphics.hpp"
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

void Graphics::drawBox(Vector center, int width, int height, float angle, Color::Pixel color)
{
  ScopedPrinter printer("void Graphics::drawBox(Vector center, int width, int height, float angle, Color::Pixel color)");

  float wper2 = width / 2.0f;
  float hper2 = height / 2.0f;

  Polygon polygon{rotate(Vector(wper2, hper2), angle) + center,
                  rotate(Vector(wper2, -hper2), angle) + center,
                  rotate(Vector(-wper2, -hper2), angle) + center,
                  rotate(Vector(-wper2, hper2), angle) + center};

  DrawFunctions::drawPolygon(polygon, *m_buffer, color);
}

void Graphics::drawPolygon(const Polygon& polygon, Color::Pixel color)
{
  DrawFunctions::drawPolygon(polygon, *m_buffer, color);
}

void Graphics::clearBuffer()
{
  std::memset(m_buffer->pixels, 0xff, m_buffer->w * m_buffer->h * (32 / 8));
}
