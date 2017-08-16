#include "CHeavyType.h"



CHeavyType::CHeavyType()
{
	m_iID = 0;
	m_iMaxGarrison = 0;
	m_iProductionCosts = 0;
	m_bCanRecolect = 0;
	m_bCanBuild = 0;
	m_bIsBelic = 0;
	m_bCanGarrison = 0;
	m_bCanGroup = 0;
	m_fBuildValue = 0;
	m_fVisionRange = 0;
	m_fMaxSpeed = 0;
	m_fMaxHP = 0;
	m_fConstructionTime = 0;
	m_fRotingTime = 0;
	m_fConstructionTypes = 0;
	m_MinRange = 0;
	m_MaxRange = 10;
	m_ReloadTime = 1;
}


CHeavyType::~CHeavyType()
{
}
