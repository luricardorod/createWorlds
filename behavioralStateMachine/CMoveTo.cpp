#include "CMoveTo.h"



int CMoveTo::Update(CUnits* unit, float deltaTime)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "move_Update"))
	{
		call.End();
		int myReturn = 0;
		if (call.GetReturnedInt(myReturn))
		{
			return myReturn;
		}
		else
		{
			std::cout << "move_Update returned an incorrect value" << std::endl;
		}
	}
	else
	{
		std::cout << "error move_Update" << std::endl;
	}
	return COUNTSTATES;
}

void CMoveTo::OnEnter(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "move_OnEnter"))
	{
		call.End();
	}
	else
	{
		std::cout << "error move_OnEnter" << std::endl;
	}
}

void CMoveTo::OnExit(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "move_OnExit"))
	{
		call.End();
	}
	else
	{
		std::cout << "error move_OnExit" << std::endl;
	}
}

CMoveTo::CMoveTo()
{
}


CMoveTo::~CMoveTo()
{
}
