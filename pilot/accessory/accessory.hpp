#pragma once

#include <vector>

#include "basic_elements.hpp"
#include "controls.hpp"

class Flyer;
class Framework;

#define ACCESSORY_PARAMETERS const Vector& anchor, Direction direction, Flyer& flyer, Framework& framework
#define INITIALIZE_ACCESSORY_BASE() Accessory(anchor, direction, flyer, framework)

class Accessory
{
  public:
    virtual ~Accessory()
    { }

    typedef std::vector<Controls::ControlEntity> ControlArray;
    const ControlArray& getControls() const
    {
      return m_controls;
    }

    virtual void mainEvent()
    {
    }

  protected:
    Accessory(ACCESSORY_PARAMETERS): m_anchor(anchor), m_direction(direction), m_flyer(flyer), m_framework(framework), m_controls()
    { }
    
    void addControl(const Controls::ControlEntity& control)
    {
      m_controls.push_back(control);
    }
    
    ControlArray& controls()
    {
      return m_controls;
    }
    
    Vector& anchor()
    {
      return m_anchor;
    }
    
    Direction& direction()
    {
      return m_direction;
    }
    
    Flyer& flyer()
    {
      return m_flyer;
    }
    
    Framework& framework()
    {
      return m_framework;
    }

  private:
    Vector        m_anchor;
    Direction     m_direction;
    Flyer&        m_flyer;
    Framework&    m_framework;

    ControlArray  m_controls;
};
