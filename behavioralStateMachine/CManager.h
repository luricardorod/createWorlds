#pragma once
#include "CTypes.h"
#include "CFaction.h"
#include "CWeaponType.h"
#include <vector>
class CManager
{
public:
	CTypes* GetType(int id);
	CFaction* GetFaction(int id);
	CWeaponType* GetWeaponType(int id);
	std::vector<CTypes*> m_aTypes;
	std::vector<CFaction*> m_aFactions;

	CWeaponType* m_aWeapons;
	CManager();
	~CManager();
};

