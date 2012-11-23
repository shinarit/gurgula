#pragma once

#include <iostream>
#include <string>

struct ScopedPrinter
{
  ScopedPrinter(const std::string& str): m_str(str)
  {
    //std::cerr << m_str << " entered\n";
  }
  ~ScopedPrinter()
  {
    //std::cerr << m_str << " left\n";
  }
  std::string m_str;
};

