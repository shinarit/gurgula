#ifndef _DRAWFUNCTIONS_HPP_
#define _DRAWFUNCTIONS_HPP_

class SDL_Surface;
typedef uint32_t Pixel;

void drawCircle(int x0, int y0, int radius, SDL_Surface& surface, Pixel color = 0);
void drawLine(int x1, int y1, int x2, int y2, SDL_Surface& surface, Pixel color = 0);

#endif
