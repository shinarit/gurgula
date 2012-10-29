#ifndef _BASIC_ELEMENTS_HPP_
#define _BASIC_ELEMENTS_HPP_

#include <vector>

#include <Box2D/Common/b2Math.h>

typedef b2Vec2 Vector;
//should be "uncomplete", meaning the last and the first vertex shouldnt be the same
typedef std::vector<Vector> Polygon;

#endif
