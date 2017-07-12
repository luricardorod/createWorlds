#include "CGarrison.h"



int CGarrison::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	if (unit->m_UnitInteract && unit->m_Manager->GetType(unit->m_UnitInteract->m_iIdType)->m_bCanGarrison)
	{
		unit->m_v2Direction = (unit->m_UnitInteract->GetPosition() - unit->GetPosition());
		float distance = unit->m_v2Direction.Magnitude();
		if (distance < GARRISONRADIUSENTRANCE)
		{
			if (unit->CanEnter(unit->m_UnitInteract))
			{
				unit->m_UnitInteract->m_vListaGarrison->push_back(unit);
				return COUNTSTATES;
			}
		}
	}
	return STATEIDLE;
}

void CGarrison::OnEnter(CUnits *unit)
{
}

void CGarrison::OnExit(CUnits *unit)
{
	for (auto it = unit->m_UnitInteract->m_vListaGarrison->begin(); it != unit->m_UnitInteract->m_vListaGarrison->end(); it++) {
		if (it->get() == unit)
		{
			unit->m_UnitInteract->m_vListaGarrison->erase(it);
		}
	}
}

CGarrison::CGarrison()
{
}


CGarrison::~CGarrison()
{
}
