#ifndef __ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__
#define __ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__

#include <Windows.h>

#define SHAREMEMORY_MAPPING_NAME L"AskTao_ShareMemory_Name"

enum em_Script_Status
{
	em_Script_Status_None,
	em_Script_Status_Running,
	em_Script_Status_Stop
};

struct ConsoleShareMemoryContent
{
	WCHAR wszConsoleDirectory[MAX_PATH];
	em_Script_Status emScriptStatus;
};


#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__
