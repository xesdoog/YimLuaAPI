/**
 * @file view_main.cpp
 * @brief Main window you can add new tabs - tab bars here.
 */

#ifdef ENABLE_GUI

#include "lua/lua_manager.hpp"
#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::main_view()
	{
		if (ImGui::Begin("Main", &g.window.main))
		{
			if (ImGui::BeginTabBar("tabbar"))
			{
				g_lua_manager->draw_tabs();

				if (ImGui::BeginTabItem("Debug"))
				{
					view::debug_tabs();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}

#endif
