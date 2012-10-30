#include <cmath>

#include "basic_elements.hpp"

Vector rotate(const Vector& vector, float angle)
{
  float cosine = std::cos(angle);
  float sine = std::sin(angle);
  
  return Vector(vector.x * cosine - vector.y * sine, vector.x * sine + vector.y * cosine);
}
