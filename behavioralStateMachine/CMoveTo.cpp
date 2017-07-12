#include "CMoveTo.h"



int CMoveTo::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	unit->m_v2Direction = unit->m_v2Coordinates - unit->GetPosition();
	float distance = unit->m_v2Direction.Magnitude();
	if (distance < ARRIVALMARGINERROR)
	{
		return STATEIDLE;
	}
	return COUNTSTATES;
}

void CMoveTo::OnEnter(CUnits *unit)
{
}

void CMoveTo::OnExit(CUnits *unit)
{
}

CMoveTo::CMoveTo()
{
}


CMoveTo::~CMoveTo()
{
}
