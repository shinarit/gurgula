#ifndef _RAII_CLASSES_HPP_
#define _RAII_CLASSES_HPP_

template<class T>
struct CustomDeleteRaii
{
  typedef T* Tptr;
  typedef void (*FreeFunction)(Tptr);
  CustomDeleteRaii(T* ptr, FreeFunction free): m_ptr(ptr), m_free(free)
  { }
  ~CustomDeleteRaii()
  {
    m_free(m_ptr);
  }
  operator Tptr()
  {
    return m_ptr;
  }
  T* operator->() { return m_ptr; }
  T& operator*() { return *m_ptr; }

  T*            m_ptr;
  FreeFunction  m_free;
};


#endif
