#include "CDead.h"

int CDead::Update(CUnits* unit, float deltaTime)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "dead_Update"))
	{
		call.End();
		int myReturn = 0;
		if (call.GetReturnedInt(myReturn))
		{
			return myReturn;
		}
		else
		{
			std::cout << "dead_Update returned an incorrect value" << std::endl;
		}
	}
	else
	{
		std::cout << "error dead_Update" << std::endl;
	}
	return STATEROTING;
}

void CDead::OnEnter(CUnits *unit)
{

	gmCall  call;
	if (call.BeginGlobalFunction(gm, "dead_OnEnter"))
	{
		call.End();
	}
	else
	{
		std::cout << "error dead_OnEnter" << std::endl;
	}
}

void CDead::OnExit(CUnits *unit)
{
	gmCall  call;
	if (call.BeginGlobalFunction(gm, "dead_OnExit"))
	{
		call.End();
	}
	else
	{
		std::cout << "error dead_OnExit" << std::endl;
	}
}

CDead::CDead()
{
}


CDead::~CDead()
{
}
