#include "CManager.h"

CManager::CManager()
{
}


CManager::~CManager()
{
}

CTypes* CManager::GetType(int id)
{
	return &m_aTypes[id];
}

CFaction* CManager::GetFaction(int id)
{
	return &m_aFactions[id];
}

CWeaponType* CManager::GetWeaponType(int id)
{
	return &m_aWeapons[id];
}