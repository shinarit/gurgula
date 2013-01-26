#pragma once

#include "accessory.hpp"

class RocketEngine: public Accessory
{
  public:
    RocketEngine(ACCESSORY_PARAMETERS);

    virtual void mainEvent();

  private:
    bool    m_on;
};
