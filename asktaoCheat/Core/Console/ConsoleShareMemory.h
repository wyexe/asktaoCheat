#ifndef __ASKTAOCHEAT_GAMEDLL_CORE_CONSOLE_CONSOLESHAREMEMORY_H__
#define __ASKTAOCHEAT_GAMEDLL_CORE_CONSOLE_CONSOLESHAREMEMORY_H__

#include <Core/Common/GameStruct.h>
#include <future>

class CConsoleShareMemory
{
public:
	CConsoleShareMemory() = default;
	~CConsoleShareMemory();

	static CConsoleShareMemory& GetInstance();
public:

	// Read Console Share Memory Mapping to here
	// 读取控制台的内存共享数据
	BOOL Initialize();

private:
	// Watch Console Memory => Is Run Script ...
	// 监视控制台的指令
	VOID AsyncWatchConsole();

private:
	ConsoleShareMemoryContent*  _pConsoleShareMemory	= nullptr;
	HANDLE						_hFileMapping			= NULL;
	std::future<VOID>			_AsyncWatchConsolePtr;
	BOOL						_RunThread				= FALSE;
};



#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_CONSOLE_CONSOLESHAREMEMORY_H__
