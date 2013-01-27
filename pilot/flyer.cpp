#include "flyer.hpp"

Flyer::Flyer(b2Body* body): m_body(body), m_ids(), m_accessories()
{ }

Flyer::Flyer(Flyer&& other)
            : m_body(other.m_body)
            , m_ids(other.m_ids)
            , m_accessories(std::move(other.m_accessories))
{
  
}

Flyer& Flyer::operator=(Flyer&& other)
{
  m_body = other.m_body;
  m_ids = other.m_ids;
  
  m_accessories.clear();
  m_accessories.assign(std::make_move_iterator(std::begin(other.m_accessories)), std::make_move_iterator(std::end(other.m_accessories)));
  
  return *this;
}

void Flyer::AddAccessory(AccessoryRef accessory)
{
  m_accessories.push_back(std::move(accessory));
}

void Flyer::applyForce(const Vector& where, const Vector& vector)
{
  
}
