#include "CDead.h"



int CDead::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	return STATEROTING;
}

void CDead::OnEnter(CUnits *unit)
{
	unit->m_bSelectable = false;

}

void CDead::OnExit(CUnits *unit)
{
}

CDead::CDead()
{
}


CDead::~CDead()
{
}
