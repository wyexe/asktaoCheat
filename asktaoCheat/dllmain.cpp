#include <Windows.h>
#include <Core/Command/Command.h>

em_Script_Status g_emScriptStatus = em_Script_Status_None;

BOOL WINAPI DllMain(
	_In_ HINSTANCE ,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    )
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		
	}
	return TRUE;
}