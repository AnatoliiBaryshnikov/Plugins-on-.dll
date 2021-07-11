// The simple example of the dll-based plugins run-time attaching 
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <string>
#include "IPlugin.h"

using dll_func = void*(*)();

const std::vector<std::filesystem::path> get_dll_paths(const std::string& plugin_dir);

int main()
  {
  const std::string plugin_dir = "./plugins/";
  const std::string plugin_func_name = "GetPluginInstance";
  const std::vector<std::filesystem::path> dll_paths = get_dll_paths(plugin_dir);

  if (dll_paths.size() == 0)
    {
    std::cerr << "No plugins are uploaded! So sorry... \n";
    return 1;
    }

  for (const auto& path : dll_paths)
    {
    auto LoadedDll = LoadLibrary(path.c_str());
    if (!LoadedDll)
      {
      std::cout << "Can`t load [" << path << "]\n";
      continue;
      }

    auto func = reinterpret_cast<dll_func>(GetProcAddress(LoadedDll, plugin_func_name.c_str()));
    if (!func)
      {
      std::cout << "Warning! Can`t access IPlugin member function in plugin [" << path << "]\n";
      FreeLibrary(LoadedDll); // I don`t know if this is really needed, but somewhere is recommended
                              // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-freelibrary
      continue;
      }

    auto plugin = static_cast<IPlugin*>(func()); // Raw pointer management because of FreeLibrary()
    plugin->GetPluginName();
    delete plugin;
    plugin = nullptr;

    FreeLibrary(LoadedDll); // I don`t know if this is really needed, but somewhere is recommended
                            // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-freelibrary
    }

  std::cout << "Work is done! Goodbye!\n";
  system("pause");
  return 0;
  }

/// <summary>
/// This function realizes the logics of iterating over given directory, filtering dll files
/// and adding their path to vector. Also it handles some i/o errors.
/// </summary>
/// <param name="plugin_dir"> - path to directory with .dll files (plugins) </param>
/// <returns></returns>
const std::vector<std::filesystem::path> get_dll_paths(const std::string& plugin_dir)
  {
  std::vector<std::filesystem::path> dll_paths;

  try
    {
    std::cout << "In [" << plugin_dir << "] the following .dll`s are present: \n";

    for (const auto& p : std::filesystem::directory_iterator(plugin_dir))
      {
      if (p.path().extension() == ".dll")
        {
        std::cout << "  " << p.path() << "\n";
        dll_paths.push_back(p.path());
        }
      }
    }
  catch (const std::exception& e)
    {
    std::cerr << "!!! Error occured: " << "[" << e.what() << "]\n\n" ;
    }

  return dll_paths;
  }