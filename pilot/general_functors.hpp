#pragma once

#define TEMPLATE_ARGUMENTS class ReturnType, class ... Args
#define TEMPLATE_ARGUMENTS_ACTUALIZED ReturnType, Args...
#define TEMPLATE_FUNCTION(name) ReturnType name(Args ... args)

namespace functors
{
  template <TEMPLATE_ARGUMENTS>
  class VirtualFunctor
  {
    public:
      virtual ~VirtualFunctor()
      { }
      TEMPLATE_FUNCTION(operator())
      {
        return call(args...);
      }
      
    private:
      virtual TEMPLATE_FUNCTION(call) = 0;
  };

  template <TEMPLATE_ARGUMENTS>
  class FreeFunction: public VirtualFunctor<TEMPLATE_ARGUMENTS_ACTUALIZED>
  {
    public:
      typedef ReturnType (*CallType)(Args...);
      FreeFunction(CallType function): m_function(function)
      { }

    private:
      virtual TEMPLATE_FUNCTION(call)
      {
        return m_function(args...);
      }
    
      CallType m_function;
  };

  template <class T, TEMPLATE_ARGUMENTS>
  class MemberFunction: public VirtualFunctor<TEMPLATE_ARGUMENTS_ACTUALIZED>
  {
    public:
      typedef ReturnType (T::*CallType)(Args...) ;
      MemberFunction(T* object, CallType function): m_object(object), m_function(function)
      { }
    
    private:
      virtual TEMPLATE_FUNCTION(call)
      {
        return (m_object->*m_function)(args...);
      }
    
      T*        m_object;
      CallType  m_function;
  };

  template <TEMPLATE_ARGUMENTS>
  VirtualFunctor<TEMPLATE_ARGUMENTS_ACTUALIZED>* createFromFreeFunction(ReturnType (*freeFunction)(Args...))
  {
    return new FreeFunction<TEMPLATE_ARGUMENTS_ACTUALIZED>(freeFunction);
  }

  template <class T, TEMPLATE_ARGUMENTS>
  VirtualFunctor<TEMPLATE_ARGUMENTS_ACTUALIZED>* createFromMemberFunction(T* object, ReturnType (T::*memberFunction)(Args...))
  {
    return new MemberFunction<T, TEMPLATE_ARGUMENTS_ACTUALIZED>(object, memberFunction);
  }
}

#undef TEMPLATE_ARGUMENTS
#undef TEMPLATE_ARGUMENTS_ACTUALIZED
#undef TEMPLATE_FUNCTION
