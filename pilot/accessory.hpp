#pragma once

#include "basic_elements.hpp"

#include <vector>

struct ControlEntity
{
  enum class ControlType
  {
    TOGGLE,
    PRESSED,
    PRESS_ONCE,
    DIRECTION,
    POSITION
  };
  enum class DirectionState
  {
    TURNING_LEFT,
    TURNING_RIGHT,
    IDLE
  };
  struct DirectionControl
  {
    DirectionState state;
    Direction direction;
  };
  ControlType type;
  union
  {
    bool toggled;               //changes when button is pressed
    bool pressed;               //true while button is pressed
    bool shot;                  //true for one round after button is pressed
    DirectionControl direction; //stores if we should change the direction. the direction value is needed for mouse controls
    Vector position;
  };
};

class Accessory
{
  public:
    typedef std::vector<ControlEntity> ControlArray;
    const ControlArray& getControls() const;
  protected:
    template <class Iter>
    Accessory(Iter begin, Iter end): m_controls(begin, end)
    { }
  private:
    ControlArray m_controls;
};
