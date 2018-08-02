#include <Windows.h>
#include <Core/Console/ConsoleShareMemory.h>


BOOL WINAPI DllMain(
	_In_ HINSTANCE ,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    )
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (!CConsoleShareMemory::GetInstance().Initialize())
		{
			::MessageBoxW(NULL, L"Read Console ShareMemory Faild!!!", L"", NULL);
			return FALSE;
		}
	}
	return TRUE;
}