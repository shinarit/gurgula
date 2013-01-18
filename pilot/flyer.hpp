#pragma once

#include <memory>
#include <vector>

#include "identifier.hpp"
#include "accessory.hpp"

class b2Body;

//
// every object that has a physical body is a flyer
// basically its the game world equivalent for a box2d body
//

class Flyer
{
public:
  Flyer(b2Body& body);
  
  typedef std::unique_ptr<Accessory> AccessoryRef;
  void AddAccessory(AccessoryRef accessory);

protected:
  Identifier    m_ids;
  typedef std::vector<AccessoryRef> Accessories;
  Accessories   m_accessories;
};

