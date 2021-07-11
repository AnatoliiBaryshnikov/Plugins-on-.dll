// Simple interface that provides interaction with plugins
//

#pragma once

#include <string>

class IPlugin
	{
		public:
		IPlugin() = default;
		virtual ~IPlugin() = default;

		virtual void GetPluginName() = 0;
	};