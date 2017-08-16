#include "CIdle.h"


int CIdle::Update(CUnits* unit, float deltaTime)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "idle_Update"))
	{
		call.AddParamInt(unit->m_Manager->m_aTypes[unit->m_iIdType]->m_bIsBelic);
		call.AddParamInt(unit->EnemyInVisionRange());

		call.End();
		int myReturn = 0;
		if (call.GetReturnedInt(myReturn))
		{
			return myReturn;
		}
		else
		{
			std::cout << "idle_Update returned an incorrect value" << std::endl;
		}
	}
	else
	{
		std::cout << "error idle_Update" << std::endl;
	}

	return STATEIDLE;
}

void CIdle::OnEnter(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "idle_OnEnter"))
	{
		call.End();
	}
	else
	{
		std::cout << "error idle_OnEnter" << std::endl;
	}
}

void CIdle::OnExit(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "idle_OnExit"))
	{
		call.End();
	}
	else
	{
		std::cout << "error idle_OnExit" << std::endl;
	}
}

CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
