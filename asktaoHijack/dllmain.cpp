#include <Windows.h>
#include <Shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")

DWORD WINAPI _LoadThread(LPVOID)
{
	WCHAR wszFileName[MAX_PATH] = { 0 };
	::GetModuleFileNameW(NULL, wszFileName, MAX_PATH - 1);
	::PathRemoveFileSpecW(wszFileName);
	::lstrcatW(wszFileName, L"\\GameDLL.dll");
	if (::LoadLibraryW(wszFileName) == NULL)
	{
		::MessageBoxW(NULL, L"Load GameDLL.dll Faild!", L"Hijack Error", NULL);
	}
	return 0;
}

BOOL WINAPI DllMain(_In_ HMODULE, _In_ DWORD dwReason, _In_ LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)_LoadThread, NULL, NULL, NULL);
	}
	return TRUE;
}