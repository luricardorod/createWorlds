#pragma once
#include "CStates.h"
#include <vector>
#include <memory>
class CFSM
{
public:
	CStates** m_States;
	void SetState(CUnits *unit,int state);
	void Update(float deltaTime);

	std::vector<std::shared_ptr<CUnits>> m_pUnits;
	CFSM();
	~CFSM();
};

