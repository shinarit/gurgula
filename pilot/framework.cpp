#include "framework.hpp"

#include "event_server.hpp"

Framework::Framework(EventServer& eventServer): m_eventServer(eventServer)
{ }

void Framework::addBinding(KeyCode code, const Controls::ControlEntity& control)
{
  //m_keyBindings.insert(std::make_pair(code, ));
}
