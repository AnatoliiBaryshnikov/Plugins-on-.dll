// This is Plugin #2
//

#include <iostream>
#include "IPlugin.h"

class PluginSecond : public IPlugin
  {
    public:
    void GetPluginName() override
      {
      std::cout << "  >>> Member function of Plugin #2 is accessed! Wow, success 8D !\n";
      }
  };

extern "C" __declspec(dllexport) void* GetPluginInstance()
  {
  return static_cast<void*> (new PluginSecond);
  }