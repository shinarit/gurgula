#pragma once

namespace Controls
{
  enum class ControlType
  {
    TOGGLED,
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
  
  struct ControlEntity
  {
    public:
      static ControlEntity createToggled(bool* toggled)
      {
        return ControlEntity(ControlType::TOGGLED, toggled);
      }
      static ControlEntity createPressed(bool* pressed)
      {
        return ControlEntity(ControlType::PRESSED, pressed);
      }
      static ControlEntity createPressOnce(bool* button)
      {
        return ControlEntity(ControlType::PRESS_ONCE, button);
      }
      static ControlEntity createDirection(DirectionControl* directionControl)
      {
        return ControlEntity(ControlType::DIRECTION, directionControl);
      }
      static ControlEntity createToggled(Vector* position)
      {
        return ControlEntity(ControlType::POSITION, position);
      }
    private:
      ControlEntity(ControlType type, void* data): type(type), data(data)
      { }
      ControlType type;
      void*       data;
//        bool toggled;               //changes when button is pressed
//        bool pressed;               //true while button is pressed
//        bool shot;                  //true for one round after button is pressed
//        DirectionControl direction; //stores if we should change the direction. the direction value is needed for mouse controls
//        Vector position;
  };
}
