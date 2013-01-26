#pragma once

#include "basic_elements.hpp"
#include "controls.hpp"

#include <vector>

#define ACCESSORY_PARAMETERS const Vector& anchor, const Vector& direction
#define INITIALIZE_ACCESSORY_BASE() Accessory(anchor, direction)

class Accessory
{
  public:
    typedef std::vector<Controls::ControlEntity> ControlArray;
    const ControlArray& getControls() const
    {
      return m_controls;
    }

    virtual void mainEvent()
    {
    }

  protected:
    Accessory(ACCESSORY_PARAMETERS): m_anchor(anchor), m_direction(direction), m_controls()
    { }
    virtual ~Accessory()
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
    
    Vector& direction()
    {
      return m_direction;
    }

  private:
    Vector        m_anchor;
    Vector        m_direction;

    ControlArray  m_controls;
};
