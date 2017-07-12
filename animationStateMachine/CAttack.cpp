#include "CAttack.h"



int CAttack::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	if (unit->m_UnitInteract)
	{
		
	}
	return STATEIDLE;
}

void CAttack::OnEnter(CUnits *unit)
{
}

void CAttack::OnExit(CUnits *unit)
{
}

CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}
