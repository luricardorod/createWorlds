#pragma once
#include "CStates.h"
class CRecollect :
	public CStates
{
public:
	int Update(std::shared_ptr<CUnits> unit, float deltaTime);
	void OnEnter(CUnits *unit);
	void OnExit(CUnits *unit);
	CRecollect();
	~CRecollect();
};

