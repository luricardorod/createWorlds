#pragma once
#include "CTypes.h"
#include "CFaction.h"
#include "CWeaponType.h"

class CManager
{
public:
	CTypes* GetType(int id);
	CFaction* GetFaction(int id);
	CWeaponType* GetWeaponType(int id);
	CTypes* m_aTypes;
	CFaction* m_aFactions;
	CWeaponType* m_aWeapons;
	CManager();
	~CManager();
};

