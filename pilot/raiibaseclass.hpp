#pragma once

template<class T>
struct CustomDeleteRaii
{
  typedef T* Tptr;
  typedef void (*FreeFunction)(Tptr);
  CustomDeleteRaii(T* ptr, FreeFunction free): m_ptr(ptr), m_free(free)
  { }
  CustomDeleteRaii(const CustomDeleteRaii&) = delete;

  CustomDeleteRaii& operator=(const CustomDeleteRaii&) = delete;
 
  operator Tptr()
  {
    return m_ptr;
  }
  T* operator->() { return m_ptr; }
  T& operator*() { return *m_ptr; }

  T*            m_ptr;
  FreeFunction  m_free;
  
protected:
  ~CustomDeleteRaii()
  {
    m_free(m_ptr);
  }
};

