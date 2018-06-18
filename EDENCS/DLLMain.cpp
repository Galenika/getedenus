#include "Interfaces.h"
#include "Hooks.h"
#include "Render.h"
#include "SDK.h"

#include "recvproxy.h"
#include "Misc.h"

bool unload;

bool on_dll_attach(void* base)
{
#ifdef Bread
	U::OpenConsole("EDEN - Developer Console");
#endif // Bread

	//U::OpenConsole("EDEN - Developer Console");
	InitialiseInterfaces();
	g_Netvars->GetNetvars();
	g_Render->SetupFonts();
	hooks::initialize();
	NetvarHook();

	while (unload == false)
	{
		Sleep(1000);
	}


	UnloadProxy();
	hooks::cleanup();

	Sleep(2000);
	FreeLibraryAndExitThread((HMODULE)base, 0);
}

bool on_dll_detach()
{
	U::CloseConsole();
	UnloadProxy();
	hooks::cleanup();
	return 1;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_	LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	// in this file we're going to bypass the new hook detection.
 	
	// bypassing this is super hard and we need to add an extra layer of protection so i will install a trojan
	// install.trojan = 1;
	hack->vmtbypass()
	// trojan installed: 
	// https://target.scene7.com/is/image/Target/50019256_Alt01?wid=488&hei=488&fmt=pjpeg
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return on_dll_detach();
	}
	return TRUE;
}

