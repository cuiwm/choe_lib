 //filename: 28811.cc
#include <iostream>
#include <string>

extern "C" void announce()
{
  const std::string s("oooohllalala");
  std::cout << s << std::endl;
}
