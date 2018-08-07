#ifndef __ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_CALL_GAMECALL_H__
#define __ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_CALL_GAMECALL_H__


#include <Windows.h>

class CGameCALL
{
public:
	using SendCALLPtr = BOOL(WINAPIV*)(...);
	using FightCALLPtr = BOOL(WINAPIV*)(...);
	static SendCALLPtr	_SendPtr;
	static FightCALLPtr _FightPtr;
public:
	CGameCALL() = default;
	~CGameCALL() = default;

	static VOID UseItem_NoFight(_In_ DWORD dwItemId);

	static VOID NormalAttack(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId);

	static VOID Defence(_In_ DWORD dwInvokeId);

	static VOID UseItem(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId, _In_ DWORD dwItemId);

	static VOID UseSKill(_In_ DWORD dwInvokeId, _In_ DWORD dwTarId, _In_ DWORD dwSkillId);

	static VOID Tranfer(_In_ DWORD dwPlayerId, _In_ DWORD dwItemId, _In_ LPCSTR pszMapInfo);
private:
	static CHAR         _szEmptyText[32];
};




#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_CALL_GAMECALL_H__
