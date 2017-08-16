#pragma once
#include "CStates.h"
class CGarrison :
	public CStates
{
public:
	int Update(CUnits* unit, float deltaTime);
	void OnEnter(CUnits *unit);
	void OnExit(CUnits *unit);
	CGarrison();
	~CGarrison();
};

