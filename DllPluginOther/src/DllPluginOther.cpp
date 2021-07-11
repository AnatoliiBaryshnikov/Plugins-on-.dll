// This is some other plugin, that does not contain IPlugin - 
// just to test program behaviour.

#include <iostream>

extern "C" __declspec(dllexport) void SomeOtherFunc()
  {
  std::cout << "You won`t see this \n";
  }