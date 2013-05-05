#pragma once

#include <memory>
#include <map>
#include <functional>

#include "general_functors.hpp"
#include "eventtypes.hpp"
#include "basic_elements.hpp"

class EventServer
{
  public:
    EventServer() = default;

    EventServer(const EventServer&&) = delete;
    EventServer& operator=(const EventServer&&) = delete;
    
    EventServer(const EventServer&) = delete;
    EventServer& operator=(const EventServer&) = delete;

    ~EventServer() = default;
    
    typedef int ListenerId;
    template <class Event>
    using Handler = std::function<void(const Event&)>;

    template <class Event, class CallbackCompatible>
    ListenerId addListener(const typename Event::Filter& filter, CallbackCompatible callback_compatible)
    {
      auto it = m_dispatchers.find(Event::eventType);
      if (it == end(m_dispatchers))
      {
        it = m_dispatchers.insert(std::move(std::make_pair(Event::eventType, std::move(make_unique<Dispatcher<Event>>())))).first;
      }
      return (static_cast<Dispatcher<Event>*>(it->second.get()))->addListener(filter, std::move(Handler<Event>(callback_compatible)));
    }

    template <class Event>
    void dispatchEvent(Event event)
    {
      auto it = m_dispatchers.find(Event::eventType);
      if (it != end(m_dispatchers))
      {
        (static_cast<Dispatcher<Event>*>(it->second.get()))->sendEvent(event);
      }
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
        ListenerId addListener(const typename Event::Filter& filter, Handler<Event> callback)
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
        {
          for (auto& it: m_callbacks)
          {
            auto& filter(it.first);
            if (filter.filter(event))
            {
              it.second(event);
            }
          }
        }
        
      private:
        std::map<ListenerId, std::pair<typename Event::Filter, Handler<Event>>> m_callbacks;
        ListenerId                                                              m_currId;
    };
    
    std::map<EventType, std::unique_ptr<DispatcherInterface>>   m_dispatchers;
};
