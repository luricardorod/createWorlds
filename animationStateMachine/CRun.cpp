#include "CIdle.h"


int CIdle::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	CTypes *tempType = unit->m_World->GetType(unit->m_iIdType);
	
	if (unit->IsBelic())
	{
		if (unit->EnemyInVisionRange())
		{
			return STATEATTACK;
		}
	}
	return COUNTSTATES;
}

void CIdle::OnEnter(CUnits *unit)
{
}

void CIdle::OnExit(CUnits *unit)
{
}

CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
