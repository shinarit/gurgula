#include "framework.hpp"

#include "event_server.hpp"

Framework::Framework(EventServer& eventServer): m_eventServer(eventServer)
{ }

Framework::BindId Framework::addBinding(KeyCode code, const Controls::ControlEntity& control)
{
  auto idControlPair = createBinding(code, control);
  m_keyBindings.insert(std::move(idControlPair));
  return 0; //TODO wtf
}

Framework::KeyBindMap::value_type Framework::createBinding(KeyCode code, const Controls::ControlEntity& control)
{
  //KeyControl* 
}
