#include <stdint.h>

#include "lan.hpp"
#include "utils/memory.hpp"

volatile uint8_t * const g_VersusLanFlag = reinterpret_cast<volatile uint8_t *>(0x022870c4);

void HostLanLobby_Detour()
{
	WriteProcessMemory(sys_process_getpid(), (void*)g_VersusLanFlag, (void*)"\x01", 1);
}

void JoinLanLobby_Detour()
{
	WriteProcessMemory(sys_process_getpid(), (void*)g_VersusLanFlag, (void*)"\x00", 1);
}
