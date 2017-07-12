#pragma once
#include <memory>
#include "CUnits.h"

enum STATES
{
	STATEATTACK,
	STATEDEAD,
	STATEIDLE,
	STATEMOVETO,
	COUNTSTATES
};
class CStates
{
public:
	virtual int Update(std::shared_ptr<CUnits> unit, float deltaTime) = 0;
	virtual void OnEnter(CUnits *unit) = 0;
	virtual void OnExit(CUnits *unit) = 0;
	virtual ~CStates() {};
};

