/*!
	@file
	@author		Albert Semenov
	@date		02/2010
*/

#include "Plugin.h"
#include "MyGUI_LogManager.h"
#include "MyGUI_PluginManager.h"

namespace plugin
{

	const std::string Plugin::LogSection = "Plugin";

	Plugin::Plugin()
	{
		MyGUI::LogManager::registerSection(Plugin::LogSection, MYGUI_LOG_FILENAME);
	}

	Plugin::~Plugin()
	{
		MyGUI::LogManager::unregisterSection(Plugin::LogSection);
	}

	void Plugin::install()
	{
	}

	void Plugin::uninstall()
	{
	}

	void Plugin::initialize()
	{
		MYGUI_LOGGING(LogSection, Info, "initialize");
	}

	void Plugin::shutdown()
	{
		MYGUI_LOGGING(LogSection, Info, "shutdown");
	}

	const std::string& Plugin::getName() const
	{
		static std::string type("Plugin");
		return type;
	}

} // namespace plugin

plugin::Plugin* plugin_item = 0;

extern "C" MYGUI_EXPORT_DLL void dllStartPlugin(void)
{
	plugin_item = new plugin::Plugin();
	MyGUI::PluginManager::getInstance().installPlugin(plugin_item);
}

extern "C" MYGUI_EXPORT_DLL void dllStopPlugin(void)
{
	MyGUI::PluginManager::getInstance().uninstallPlugin(plugin_item);
	delete plugin_item;
	plugin_item = 0;
}