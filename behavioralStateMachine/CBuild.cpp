#include "CBuild.h"

int CBuild::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	return 0;
}

void CBuild::OnEnter(CUnits *unit)
{

}

void CBuild::OnExit(CUnits *unit)
{

}

CBuild::CBuild()
{
}

CBuild::~CBuild()
{
}
/*
int CBuild::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
if (unit->m_fConstructionTimer > unit->m_World->GetType(unit->m_iIdType)->m_fConstructionTime)
{
return STATEIDLE;
}
else
{
unit->m_fConstructionTimer += deltaTime;
}
return COUNTSTATES;
}

void CBuild::OnEnter(CUnits *unit)
{
unit->m_fConstructionTimer = 0;
unit->m_bSelectable = false;
}

void CBuild::OnExit(CUnits *unit)
{
unit->m_bSelectable = true;
}
*/
