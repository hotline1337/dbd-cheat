#include <pch.h>
#include "hooks/hooks.h"
#include "utils/utils.h"

#include "menu/menu.h"
#include "minhook/MinHook.h"

bool __stdcall DllMain(const HMODULE module, const std::uint32_t call_reason, void* reserved [[maybe_unused]]) {
	LI_FN(DisableThreadLibraryCalls)(module);

	if (call_reason != DLL_PROCESS_ATTACH) {
		return false;
	}

	/* initialize menu */
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&menu::oPresent, menu::hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	/* main thread */
	std::future<void> thread = std::async(std::launch::async, [&module] {
		try 
		{
			utils::console::initialize("dbd-cheat");
			std::cout << "initializing...";
			sdk::initialize();
			std::cout << "ok!\n";
		}
		catch (const std::runtime_error& error) 
		{
			LI_FN(MessageBoxA)(nullptr, error.what(), _("dbd-cheat"), MB_OK | MB_ICONERROR);
			LI_FN(FreeLibraryAndExitThread)(module, 0);
		}
	});

	return true;
}