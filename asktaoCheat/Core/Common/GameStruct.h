#ifndef __ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__
#define __ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__

#include <Windows.h>
#include <ProcessLib/Memory/Memory.h>

#define SHAREMEMORY_MAPPING_NAME	L"AskTao_ShareMemory_Name"
#define MAX_PLAYERCOUNT_SHAREMEMORY 10

enum em_Script_Status
{
	em_Script_Status_None,
	em_Script_Status_Running,
	em_Script_Status_Stop
};

#define RD(Addr) libTools::CMemory::ReadDWORD(Addr)

extern em_Script_Status g_emScriptStatus;
#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_COMMON_GAMESTRUCT_H__
