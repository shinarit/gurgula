#include "flyer.hpp"

Flyer::Flyer(b2Body& body)
{

}

void Flyer::AddAccessory(AccessoryRef accessory)
{
  m_accessories.push_back(std::move(accessory));
}
