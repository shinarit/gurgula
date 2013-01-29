#pragma once

#include <map>
#include <memory>

#include "SDL/SDL.h"
typedef SDLKey KeyCode;

#include "accessory/controls.hpp"


class Framework
{
public:
  Framework() = default;
  Framework(const Framework&) = delete;
  ~Framework() = default;
  Framework& operator=(const Framework&) = delete;

  void addBinding(KeyCode code, const Controls::ControlEntity& control);

private:
  class KeyControl
  {
  public:
    virtual ~KeyControl()
    { }
    virtual void keyDown() = 0;
    virtual void keyUp() = 0;
  };
  class PressedControl: public KeyControl
  {
  };
  typedef std::map<KeyCode, std::unique_ptr<KeyControl>>    m_keyBindings;
};
