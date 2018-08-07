#include "GameCALL.h"
#include <LogLib/Log.h>
#include <ExceptionLib/Exception.h>
#include <CharacterLib/Character.h>

#define _SELF L"GameCALL.cpp"

CGameCALL::SendCALLPtr CGameCALL::_SendPtr = reinterpret_cast<CGameCALL::SendCALLPtr>(0x6C9D80);
CGameCALL::FightCALLPtr CGameCALL::_FightPtr = reinterpret_cast<CGameCALL::SendCALLPtr>(0x0);
CHAR CGameCALL::_szEmptyText[32] = { 0 };

VOID CGameCALL::UseItem_NoFight(_In_ DWORD dwItemId)
{
	__try
	{
		CONST static CHAR szText[] = { "pos = %d" };
		_SendPtr(0x220C, szText, dwItemId);
		LOG_C_D(L"ItemPos=%X", dwItemId);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		::MessageBoxW(NULL, L"UseItem_NoFight", L"", NULL);
	}
}

VOID CGameCALL::NormalAttack(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId)
{
	__try
	{
		_FightPtr(dwInvokeId, dwTarId, 0x2, 0x0, _szEmptyText, _szEmptyText, _szEmptyText, 0, _szEmptyText);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		::MessageBoxW(NULL, L"NormalAttack", L"", NULL);
	}
}

VOID CGameCALL::Defence(_In_ DWORD dwInvokeId)
{
	__try
	{
		_FightPtr(dwInvokeId, dwInvokeId, 0x1, 0x0, _szEmptyText, _szEmptyText, _szEmptyText, 0, _szEmptyText);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		::MessageBoxW(NULL, L"Defence", L"", NULL);
	}
}

VOID CGameCALL::UseItem(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId, _In_ DWORD dwItemId)
{
	__try
	{
		_FightPtr(dwInvokeId, dwTarId, 0x4, dwItemId, _szEmptyText, _szEmptyText, _szEmptyText, 0, _szEmptyText);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		::MessageBoxW(NULL, L"UseItem", L"", NULL);
	}
}

VOID CGameCALL::UseSKill(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId, _In_ DWORD dwSkillId)
{
	__try
	{
		_FightPtr(dwInvokeId, dwTarId, 0x3, dwSkillId, _szEmptyText, _szEmptyText, _szEmptyText, 0, _szEmptyText);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		::MessageBoxW(NULL, L"UseSKill", L"", NULL);
	}
}

VOID CGameCALL::Tranfer(_In_ DWORD dwPlayerId, _In_ DWORD dwItemId, _In_ LPCSTR pszMapInfo)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, [&]
	{
		CONST static CHAR szText[] = { "id = %d, oper = %d, para1 = %d, para2 = %s" };
		static CHAR szMapText[32] = { 0 };
		memcpy(szMapText, pszMapInfo, strlen(pszMapInfo) + 1);
		_SendPtr(0x1162, szText, dwItemId, 0x1000, 0x1, szMapText);
		LOG_C_D(L"ID=%X, ItemId=%X MapInfo=[%s]", dwPlayerId, dwItemId, libTools::CCharacter::ASCIIToUnicode(szMapText).c_str());
	});
}
