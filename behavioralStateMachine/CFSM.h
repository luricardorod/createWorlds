#pragma once
#include "CStates.h"
#include <vector>
#include <memory>
#include <gmThread.h>
#include <gmCall.h>
#include "CManager.h"
class CFSM
{
public:
	void SetUnit(CUnits *unit);
	gmMachine	gm;
	CManager manager;
	void Init();
	std::vector<CStates*> m_States;
	void SetState(CUnits *unit,int state);
	void Update(float deltaTime);

	std::vector<CUnits> m_pUnits;
	CFSM();
	~CFSM();
};

