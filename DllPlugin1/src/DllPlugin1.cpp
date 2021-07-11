// This is Plugin #1
//

#include <iostream>
#include "IPlugin.h"

class PluginFirst : public IPlugin
  {
    public:
    void GetPluginName() override
      {
      std::cout << "  >>> Member function of Plugin #1 is accessed! Wow, success 8D !\n";
      }
  };

extern "C" __declspec(dllexport) void* GetPluginInstance()
  {
  return static_cast<void*> (new PluginFirst);
  }