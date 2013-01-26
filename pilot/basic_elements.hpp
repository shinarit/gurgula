#pragma once

#include <vector>

#include <Box2D/Common/b2Math.h>

typedef double Direction;
typedef double Length;

typedef b2Vec2 Vector;

//should be "uncomplete", meaning the last and the first vertex shouldnt be the same
typedef std::vector<Vector> Polygon;
typedef std::vector<Polygon> PolygonList;

//angle is in radians
Vector rotate(const Vector& vector, float angle);
//translates vector from x1 x y1 to x2 x y2
Vector distort(const Vector& vector, int x1, int y1, int x2, int y2);

//from polar
Vector fromPolar(Direction direction, Length length);
