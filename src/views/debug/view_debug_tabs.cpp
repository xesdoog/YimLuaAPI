/**
 * @file view_debug_tabs.cpp
 * @brief Debug options tab bar.
 */

#ifdef ENABLE_GUI

#include "lua/lua_manager.hpp"
#include "gta/joaat.hpp"
#include "views/view.hpp"

namespace big
{
	void view::debug_tabs()
	{
		if (ImGui::BeginTabBar("debug_tabbar"))
		{
			if (ImGui::BeginTabItem("Threads"))
			{
				view::debug_threads();
				if (g_lua_manager)
					g_lua_manager->draw_gui(RAGE_JOAAT("VIEW_DEBUG_THREADS"));
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Lua"))
			{
				view::lua_scripts();
				if (g_lua_manager)
					g_lua_manager->draw_gui(RAGE_JOAAT("GUI_TAB_LUA_SCRIPTS"));
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("GTA Cache"))
			{
				view::gta_cache();
				if (g_lua_manager)
					g_lua_manager->draw_gui(RAGE_JOAAT("GUI_TAB_GTA_CACHE_SETTINGS"));
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}

#endif
