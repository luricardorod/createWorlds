#pragma once
#include <memory>
#include "CUnits.h"
#include "CTypes.h"
#include "definitions.h"
#include <gmThread.h>
#include <gmCall.h>
#include <iostream>
class CStates
{
public:
	gmMachine*	gm;
	virtual int Update(CUnits* unit, float deltaTime) = 0;
	virtual void OnEnter(CUnits *unit) = 0;
	virtual void OnExit(CUnits *unit) = 0;
	virtual ~CStates() {};
};

