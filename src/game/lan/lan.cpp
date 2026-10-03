#include <stdint.h>

#include "lan.hpp"

volatile uint8_t * const g_VersusLanFlag = reinterpret_cast<volatile uint8_t *>(0x022870c4);

void HostLanLobby_Detour()
{
	*g_VersusLanFlag = 1;
}

void JoinLanLobby_Detour()
{
	*g_VersusLanFlag = 0;
}
