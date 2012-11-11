#include <cmath>

#include "basic_elements.hpp"

Vector rotate(const Vector& vector, float angle)
{
  float cosine = std::cos(angle);
  float sine = std::sin(angle);

  return Vector(vector.x * cosine - vector.y * sine, vector.x * sine + vector.y * cosine);
}

Vector distort(const Vector& vector, int x1, int y1, int x2, int y2)
{
  return Vector(vector.x * x2 / x1, vector.y * y2 / y1);
}
