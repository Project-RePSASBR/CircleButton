#include "hooking/hook.hpp"
#include "hooking/powerpc.hpp"
#include "lan/lan.hpp"
#include "utils/memory.hpp"

// Define hooks here
#pragma region
Hook *HostLanLobby_Hook;
Hook *JoinLanLobby_Hook;
#pragma endregion

void InstallHooks()
{
	HostLanLobby_Hook = new Hook(HOST_LAN_LOBBY_ADDR + 8, (uintptr_t)HostLanLobby_Detour, POWERPC_REGISTERINDEX_R5);
	JoinLanLobby_Hook = new Hook(JOIN_LAN_LOBBY_ADDR + 8, (uintptr_t)JoinLanLobby_Detour, POWERPC_REGISTERINDEX_R5);
}

void RemoveHooks()
{
	delete HostLanLobby_Hook;
	delete JoinLanLobby_Hook;
}
