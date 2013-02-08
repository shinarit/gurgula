#pragma once

#include <memory>
#include <vector>

#include "identifier.hpp"
#include "accessory/accessory.hpp"

class b2Body;

//
// every object that has a physical body is a flyer
// basically its the game world equivalent for a box2d body
//

class Flyer
{
  public:
    Flyer(b2Body* body);
    Flyer(const Flyer&) = delete;
    Flyer(Flyer&& other);
    Flyer& operator=(const Flyer&) = delete;
    Flyer& operator=(Flyer&& other);
    
    typedef std::unique_ptr<Accessory> AccessoryRef;
    void addAccessory(AccessoryRef accessory);
    
    void applyForce(const Vector& where, const Vector& vector);

    typedef std::vector<AccessoryRef> Accessories;
    const Accessories& getAccessories() const;

  protected:
    b2Body*       m_body;
    Identifier    m_ids;
    Accessories   m_accessories;
};

