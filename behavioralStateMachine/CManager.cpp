#include "CManager.h"
#include "CHeavyType.h"
CManager::CManager()
{
	m_aTypes.clear();
	CTypes* heavy = new CHeavyType();
	m_aTypes.push_back(heavy);
	m_aFactions.clear();
	CFaction* fac1 = new CFaction();
	fac1->m_iID = 0;
	m_aFactions.push_back(fac1);
}


CManager::~CManager()
{
}

CTypes* CManager::GetType(int id)
{
	return m_aTypes[id];
}

CFaction* CManager::GetFaction(int id)
{
	return m_aFactions[id];
}

CWeaponType* CManager::GetWeaponType(int id)
{
	return &m_aWeapons[id];
}