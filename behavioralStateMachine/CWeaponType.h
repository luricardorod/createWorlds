#pragma once
#include <vector>
#include <memory>


class CWeaponType
{
public:
	int m_Id;
	float m_MinRange;
	float m_MaxRange;
	float m_iDamage;
	float m_ReloadTime;
	std::vector<std::shared_ptr<int>> m_TerrainTypeIDs;
	bool m_bflagSplashDamage;
	float m_fSplashDamage;
	float m_fRadiusSplashDamage;
	CWeaponType();
	~CWeaponType();
};

