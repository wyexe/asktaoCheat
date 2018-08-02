#include "ConsoleShareMemory.h"

CConsoleShareMemory::~CConsoleShareMemory()
{
	// Release
	if (_pConsoleShareMemory != nullptr)
	{
		::UnmapViewOfFile(_pConsoleShareMemory);
		_pConsoleShareMemory = nullptr;
	}
	if (_hFileMapping != NULL)
	{
		::CloseHandle(_hFileMapping);
		_hFileMapping = NULL;
	}
	if (_AsyncWatchConsolePtr.valid())
	{
		_AsyncWatchConsolePtr.wait();
	}
}

CConsoleShareMemory& CConsoleShareMemory::GetInstance()
{
	static CConsoleShareMemory Instance;
	return Instance;
}

BOOL CConsoleShareMemory::Initialize()
{
	_hFileMapping = ::OpenFileMappingW(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, SHAREMEMORY_MAPPING_NAME);
	if (_hFileMapping == NULL)
		return FALSE;


	_pConsoleShareMemory = reinterpret_cast<ConsoleShareMemoryContent *>(MapViewOfFile(_hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, NULL, NULL, sizeof(ConsoleShareMemoryContent)));
	if (_pConsoleShareMemory == nullptr)
		return FALSE;


	_RunThread = TRUE;
	_AsyncWatchConsolePtr = std::async(std::launch::async, &CConsoleShareMemory::AsyncWatchConsole, this);
	return TRUE;
}

VOID CConsoleShareMemory::AsyncWatchConsole()
{
	while (_RunThread)
	{

	}
}
