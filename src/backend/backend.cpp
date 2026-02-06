/**
 * @file backend.cpp
 * @brief Main looped threads.
 */

#include "backend.hpp"

#include "looped/looped.hpp"
#include "script.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	void backend::loop()
	{
		while (g_running)
		{
			looped::system_self_globals();

			script::get_current()->yield();
		}
	}

	void backend::tunables_script()
	{
		g_tunables_service->run_script();
	}
}
