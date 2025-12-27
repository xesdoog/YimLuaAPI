#pragma once
#include "gta/fwddec.hpp"
#include <script/scrNativeHandler.hpp>

namespace big::functions
{
	using run_script_threads_t = bool (*)(std::uint32_t ops_to_execute);
	using script_vm = rage::eThreadState (*)(uint64_t* stack, int64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);

	using ptr_to_handle = Entity (*)(void*);
	using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);

	using give_pickup_rewards = void (*)(int players, uint32_t hash);

	using queue_packet = bool (*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, uint16_t* out_seq_id);

	using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);

	using request_control = void (*)(rage::netObject* net_object);

	using fidevice_get_device = rage::fiDevice* (*)(const char* path, bool allow_root);
	using fipackfile_ctor     = rage::fiPackfile* (*)(rage::fiPackfile* this_);
	using fipackfile_dtor     = rage::fiPackfile* (*)(rage::fiPackfile* this_);
	using fipackfile_open_archive = bool (*)(rage::fiPackfile* this_, const char* archive, bool b_true, int type, intptr_t very_false);
	using fipackfile_mount         = bool (*)(rage::fiPackfile* this_, const char* mount_point);
	using fipackfile_unmount       = bool (*)(const char* mount_point);
	using fipackfile_close_archive = void (*)(rage::fiDevice* this_);
}
