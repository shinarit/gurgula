#pragma once

#include "color.hpp"
#include "basic_elements.hpp"

class SDL_Surface;

namespace DrawFunctions
{
  void drawCircle(int x0, int y0, int radius, SDL_Surface& surface, Color::Pixel color = Color::BLACK);
  void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface, Color::Pixel color = Color::BLACK);
  void drawPolygon(const Polygon& polygon, SDL_Surface& surface, Color::Pixel color = Color::BLACK);
}
