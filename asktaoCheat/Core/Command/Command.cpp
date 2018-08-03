#include "Command.h"
#include <LogLib/Log.h>
#include <LogLib/CmdLog.h>
#include <CharacterLib/Character.h>
#include <HookLib/InlineHook/InlineHook.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"LogLib.lib")
#pragma comment(lib,"CharacterLib.lib")
#pragma comment(lib,"HookLib.lib")

#define _SELF L"Command.cpp"
CCommandExpr::~CCommandExpr()
{
}



std::vector<libTools::ExpressionFunPtr>& CCommandExpr::GetVec()
{
	static std::vector<libTools::ExpressionFunPtr> Vec = 
	{
		{ std::bind(&CCommandExpr::Help, this, std::placeholders::_1), L"Help" },
		{ std::bind(&CCommandExpr::Run, this, std::placeholders::_1), L"Run" },
		{ std::bind(&CCommandExpr::Stop, this, std::placeholders::_1), L"Stop" },
	};

	return Vec;
}

VOID CCommandExpr::Release()
{

}

VOID CCommandExpr::Help(CONST std::vector<std::wstring>&)
{
	for (auto& itm : GetVec())
		LOG_C_D(L"MethodName = [%s]", itm.wsFunName.c_str());
}

VOID CCommandExpr::Run(CONST std::vector<std::wstring>& Vec)
{
	if (Vec.empty())
	{
		LOG_C_D(L"Param = ");
		return;
	}

	// Run Python Script
}

VOID CCommandExpr::Stop(CONST std::vector<std::wstring>&)
{
	g_emScriptStatus = em_Script_Status_Stop;
	if (_AsyncScriptPtr.valid())
	{
		LOG_C_D(L"Waiting ...");
		_AsyncScriptPtr.wait();
	}
	LOG_C_D(L"Stoped");
}

//////////////////////////////////////////////////////////////////////////



CCommand::PeekMessageADef CCommand::_OldPeekMessageA		= nullptr;
std::atomic<bool>			CCommand::_IsExistExcuteMethod	= false;
std::function<VOID(VOID)>	CCommand::_ExcuteMethodPtr		= nullptr;
HANDLE						CCommand::_hEvent				= NULL;


CCommand::~CCommand()
{

}

CCommand& CCommand::GetInstance()
{
	static CCommand Instance;
	return Instance;
}

BOOL CCommand::Initialize(_In_ CONST std::wstring& wsPlayerName)
{
	_hEvent = ::CreateEventW(NULL, FALSE, NULL, NULL);
	libTools::CLog::GetInstance().SetClientName(wsPlayerName, libTools::CCharacter::MakeCurrentPath(L"\\Log\\"));
	if (!libTools::CInlineHook::Hook(reinterpret_cast<LPVOID>(PeekMessageA), reinterpret_cast<LPVOID>(NewPeekMessageA), reinterpret_cast<LPVOID *>(&_OldPeekMessageA)))
	{
		LOG_MSG_CF(L"Hook PeekMessageA Faild!");
		return FALSE;
	}
	

	static CCommandExpr Instance;
	return libTools::CCmdLog::GetInstance().Run(wsPlayerName, Instance.GetVec());
}

VOID CCommand::ExcutePtrToGame(_In_ std::function<VOID(VOID)> Ptr)
{
	while (_IsExistExcuteMethod)
		::Sleep(100);


	_ExcuteMethodPtr = Ptr;
	_IsExistExcuteMethod = true;
	::WaitForSingleObject(_hEvent, INFINITE);
}

BOOL WINAPI CCommand::NewPeekMessageA(_Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax, _In_ UINT wRemoveMsg)
{
	if (_IsExistExcuteMethod)
	{
		_ExcuteMethodPtr();
		::SetEvent(_hEvent);
		_IsExistExcuteMethod = false;
	}
	return _OldPeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}
