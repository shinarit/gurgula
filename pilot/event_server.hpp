#pragma once

#include <memory>
#include <map>

#include "general_functors.hpp"
#include "eventtypes.hpp"
#include "basic_elements.hpp"

class EventServer
{
  public:
    EventServer() = default;
    EventServer(const EventServer&) = delete;
    EventServer& operator=(const EventServer&) = delete;
    ~EventServer() = default;
    
    #define CALLBACK_TYPE std::unique_ptr<functors::VirtualFunctor<void, const Event&>>
    typedef int ListenerId;
    template <class Event>
    ListenerId addListener(const typename Event::Filter& filter, CALLBACK_TYPE callback)
    {
      auto it = m_dispatchers.find(Event::eventType);
      if (it == end(m_dispatchers))
      {
        it = m_dispatchers.insert(std::move(std::make_pair(Event::eventType, std::move(make_unique<Dispatcher<Event>>())))).first;
      }
      return (static_cast<Dispatcher<Event>*>(it->second.get()))->addListener(filter, std::move(callback));
    }
    
  private:
    class DispatcherInterface
    {
      public:
        virtual ~DispatcherInterface()
        {}
    };
    
    template <class Event>
    class Dispatcher: public DispatcherInterface
    {
      public:
        Dispatcher(): m_currId()
        { }
        ListenerId addListener(const typename Event::Filter& filter, CALLBACK_TYPE callback)
        {
          m_callbacks[m_currId] = std::move(std::make_pair(filter, std::move(callback)));
          return m_currId++;
        }
        void removeListener(const ListenerId& id)
        {
          auto it = m_callbacks.find(id);
          if (it != end(m_callbacks))
          {
            m_callbacks.erase(it);
          }
        }
        void sendEvent(const Event& event)
        {}
        
      private:
        std::map<ListenerId, std::pair<typename Event::Filter, CALLBACK_TYPE>>  m_callbacks;
        ListenerId                                                              m_currId;
    };
    #undef CALLBACK_TYPE
    
    std::map<EventType, std::unique_ptr<DispatcherInterface>>   m_dispatchers;
};
