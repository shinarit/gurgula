#ifndef COMMON_HPP_
#define COMMON_HPP_

//
// common stuff, small things
//
typedef unsigned char uchar;

struct Color
{
  Color(uchar red, uchar green, uchar blue): red(red), green(green), blue(blue)
  {}
  uchar red;
  uchar green;
  uchar blue;
};

//simple class containing the x, y coordinates
struct Coordinate
{
  Coordinate(int x = 0, int y = 0): x(x), y(y)
  {}
  int x;
  int y;
};

#endif
