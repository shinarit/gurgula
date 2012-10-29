#ifndef _DRAWFUNCTIONS_HPP_
#define _DRAWFUNCTIONS_HPP_

#include <vector>

#include "basic_elements.hpp"

class SDL_Surface;
typedef uint32_t Pixel;

void drawCircle(int x0, int y0, int radius, SDL_Surface& surface, Pixel color = 0);
void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface, Pixel color = 0);
typedef std::vector<Vector> Polygon;
void drawPolygon(const Polygon& polygon, SDL_Surface& surface, Pixel color = 0);

#endif
