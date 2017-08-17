#include "CAttack.h"

int CAttack::Update(CUnits* unit, float deltaTime)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "attack_Update"))
	{
		if (unit->m_fReloadTime > 0)
		{
			unit->m_fReloadTime -= deltaTime;
		}
		if (unit->m_UnitInteract)
		{
			call.AddParamFloat(unit->m_UnitInteract->GetPosition().x);
			call.AddParamFloat(unit->m_UnitInteract->GetPosition().y);
		}
		else {
			call.AddParamFloat(0);
			call.AddParamFloat(0);
		}
		call.AddParamFloat(unit->m_Manager->m_aTypes[unit->m_iIdType]->m_MaxRange);
		call.AddParamFloat(unit->m_Manager->m_aTypes[unit->m_iIdType]->m_MinRange);
		call.AddParamFloat(unit->m_Manager->m_aTypes[unit->m_iIdType]->m_ReloadTime);
		call.AddParamFloat(unit->m_fReloadTime);
		call.End();
		int myReturn = 0;
		if (call.GetReturnedInt(myReturn))
		{
			return myReturn;
		}
		else
		{
			std::cout << "updateAttack returned an incorrect value" << std::endl;
		}
	}
	else
	{
		std::cout << "error updateAttack" << std::endl;
	}
	return STATEATTACK;
}

void CAttack::OnEnter(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "attack_OnEnter"))
	{
		call.End();
	}
	else
	{
		std::cout << "error attack_OnEnter" << std::endl;
	}
}

void CAttack::OnExit(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "attack_OnExit"))
	{
		call.End();
	}
	else
	{
		std::cout << "error attack_OnExit" << std::endl;
	}
}

CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}
