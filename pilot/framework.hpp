#pragma once

#include <map>
#include <memory>

#include "SDL/SDL.h"
typedef SDLKey KeyCode;

#include "accessory/controls.hpp"

class EventServer;

class Framework
{
public:
  typedef int BindId;
  Framework(EventServer& eventServer);
  Framework(const Framework&) = delete;
  ~Framework() = default;
  Framework& operator=(const Framework&) = delete;

  BindId addBinding(KeyCode code, const Controls::ControlEntity& control);

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
  
  typedef std::map<BindId, std::unique_ptr<KeyControl>> KeyBindMap;

  KeyBindMap::value_type createBinding(KeyCode code, const Controls::ControlEntity& control);
  
  EventServer&                                              m_eventServer;
  KeyBindMap                                                m_keyBindings;
};
