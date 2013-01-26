#include "rocket_engine.hpp"

#include "flyer.hpp"

RocketEngine::RocketEngine(ACCESSORY_PARAMETERS): INITIALIZE_ACCESSORY_BASE(), m_on(false)
{
  addControl(Controls::ControlEntity::createPressed(&m_on));
}

void RocketEngine::mainEvent()
{
  if (m_on)
  {
    flyer().applyForce(anchor(), fromPolar(direction(), 10.0));
  }
}
