#include "flyer.hpp"

Flyer::Flyer(b2Body& body): m_body(body), m_ids(), m_accessories()
{

}

void Flyer::AddAccessory(AccessoryRef accessory)
{
  m_accessories.push_back(std::move(accessory));
}

void Flyer::applyForce(const Vector& where, const Vector& vector)
{
  
}
