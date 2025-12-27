/**
 * @file scripts.hpp
 * @brief Functions related to GTA 5 .ysc scipts.
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "core/data/all_script_names.hpp"
#include "fiber_pool.hpp"
#include "gta/joaat.hpp"
#include "gta/script_handler.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "gta/packet.hpp"
#include "script.hpp"
#include "script_local.hpp"
#include "services/players/player_service.hpp"

#include <memory/pattern.hpp>
#include <script/globals/GPBD_FM_3.hpp>

namespace big::scripts
{
	inline bool is_loaded(int hash)
	{
		return SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash);
	}

	inline bool is_running(int hash)
	{
		return SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash) > 0;
	}

	inline void request_script(int hash)
	{
		SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
	}

	inline int start_script_with_args(int hash, int* args, int arg_count, int stack_size)
	{
		int thread_id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(hash, args, arg_count, stack_size);
		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		return thread_id;
	}

	inline int start_script(int hash, int stack_size)
	{
		int thread_id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH(hash, stack_size);
		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		return thread_id;
	}

	inline bool wait_till_loaded(int hash)
	{
		if (is_loaded(hash))
			return true;
		for (int i = 0; i < 150 && !is_loaded(hash); i++)
			script::get_current()->yield(10ms);
		if (is_loaded(hash))
			return true;
		return false;
	}

	inline bool wait_till_running(int hash)
	{
		if (is_running(hash))
			return true;
		for (int i = 0; i < 150 && !is_running(hash); i++)
			script::get_current()->yield(10ms);
		if (is_running(hash))
			return true;
		return false;
	}

	inline bool force_host(rage::joaat_t hash)
	{
		if (auto launcher = gta_util::find_script_thread(hash); launcher && launcher->m_net_component)
		{
			auto net_component = reinterpret_cast<CGameScriptHandlerNetComponent*>(launcher->m_net_component);

			if (net_component->is_local_player_host())
			{
				return true;
			}

			net_component->do_host_migration(g_player_service->get_self()->get_net_game_player(), 0xFFFF, true);

			packet pack;
			pack.write_message(rage::eNetMessage::MsgScriptVerifyHostAck);
			net_component->m_script_handler->get_id()->serialize(&pack.m_buffer);
			pack.write<bool>(true, 1);
			pack.write<bool>(true, 1);
			pack.write<std::uint16_t>(0xFFFF, 16);

			for (auto& player : g_player_service->players())
			{
				if (player.second->get_net_game_player())
				{
					pack.send(player.second->get_net_game_player()->m_msg_id);
				}
			}

			return true;
		}

		return false;
	}

	inline int launcher_index_from_hash(rage::joaat_t script_hash)
	{
		for (int i = 0; i < launcher_scripts.size(); i++)
			if (launcher_scripts[i] == script_hash)
				return i;

		return -1;
	}

	inline const std::optional<uint32_t> get_code_location_by_pattern(rage::scrProgram* program, const memory::pattern& pattern)
	{
		uint32_t code_size = program->m_code_size;
		for (uint32_t i = 0; i < (code_size - pattern.m_bytes.size()); i++)
		{
			for (uint32_t j = 0; j < pattern.m_bytes.size(); j++)
				if (pattern.m_bytes[j].has_value())
					if (pattern.m_bytes[j].value() != *program->get_code_address(i + j))
						goto incorrect;

			return i;
		incorrect:
			continue;
		}

		return std::nullopt;
	}
}
