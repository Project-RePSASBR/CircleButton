#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>

#include "game/psasbr.hpp"

SYS_MODULE_INFO( CircleButton, 0, 1, 1);
SYS_MODULE_START( _CircleButton_prx_entry );
SYS_MODULE_STOP(_CircleButton_prx_exit);

sys_ppu_thread_t circle_button_ppu_thread = SYS_PPU_THREAD_ID_INVALID;

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _CircleButton_prx_entry(void)
{
	sys_ppu_thread_create(&circle_button_ppu_thread, [](uint64_t arg)
	{
		InstallHooks();
		sys_ppu_thread_exit(0);
	}, 0, 3000, 0x8000, SYS_PPU_THREAD_CREATE_JOINABLE, "CircleButton");

	return 0;
}

extern "C" int _CircleButton_prx_exit(void)
{
	uint64_t ret;
	sys_ppu_thread_join(circle_button_ppu_thread, &ret);
	RemoveHooks();

    return 0;
}
