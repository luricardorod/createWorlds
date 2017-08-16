#pragma once
#include "CStates.h"
class CBuild :
	public CStates
{
public:
	int Update(CUnits* unit, float deltaTime);
	void OnEnter(CUnits *unit);
	void OnExit(CUnits *unit);
	CBuild();
	~CBuild();
};

