#pragma once

namespace Color
{
  const int RED_MASK    = 0xff000000;
  const int BLUE_MASK   = 0x00ff0000;
  const int GREEN_MASK  = 0x0000ff00;

  //int should be at least 32 bits
  typedef int Pixel;
  //r, g and b should be [0, 255]
  inline Pixel Color(int red, int green, int blue)
  {
    return (red << 24) + (green << 16) + (blue << 8);
  }

  const Pixel BLACK = 0;
}

