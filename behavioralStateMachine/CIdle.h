#pragma once
#include "CStates.h"
class CIdle :
	public CStates
{
public:
	int Update(CUnits* unit, float deltaTime);
	void OnEnter(CUnits *unit);
	void OnExit(CUnits *unit);
	CIdle();
	~CIdle();
};

