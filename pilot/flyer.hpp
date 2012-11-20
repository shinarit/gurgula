#ifndef _FLYER_HPP_
#define _FLYER_HPP_

#include "identifier.hpp"

class b2Body;

//
// every object that has a physical body is a flyer
// basically its the game world equivalent for a box2d body
//
class Flyer
{
public:
  Flyer();

protected:
  Identifier m_ids;
};

#endif
