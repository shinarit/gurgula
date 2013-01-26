#pragma once

#include <vector>

#include "basic_elements.hpp"
#include "controls.hpp"

class Flyer;

#define ACCESSORY_PARAMETERS const Vector& anchor, const Vector& direction, Flyer& flyer
#define INITIALIZE_ACCESSORY_BASE() Accessory(anchor, direction, flyer)

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
    Accessory(ACCESSORY_PARAMETERS): m_anchor(anchor), m_direction(direction), m_flyer(flyer), m_controls()
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
    
    Flyer& flyer()
    {
      return m_flyer;
    }

  private:
    Vector        m_anchor;
    Vector        m_direction;
    Flyer&        m_flyer;

    ControlArray  m_controls;
};
