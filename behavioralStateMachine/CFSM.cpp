#include "CFSM.h"
#include "CIdle.h";
#include "CMoveTo.h";
#include "CAttack.h";
#include "CDead.h";
#include "CRoting.h";
#include "CRecollect.h";
#include "CBuild.h";
#include "CGarrison.h";

#include <iostream>
#include <string>
#include <fstream>
#include <iterator> 
#include <vector>

int GM_CDECL gm_myMultiply(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_INT_PARAM(a_x, 0);
	GM_CHECK_INT_PARAM(a_y, 1);

	int ret = a_x * a_y;

	a_thread->PushInt(ret);

	return GM_OK;
}

int GM_CDECL libentry(gmThread *a_thread)
{
	CUnits *p = new CUnits();
	a_thread->PushNewUser(p, GM_NULL);
	return GM_EXCEPTION;
}

int gmLoadAndExecuteScript(gmMachine &a_machine)
{
	std::vector<std::string> scripts; 

	//scripts.push_back("scripts/helloWorld.gm");
	scripts.push_back("scripts/unit.gm");
	scripts.push_back("scripts/attack.gm");
	scripts.push_back("scripts/global.gm");
	scripts.push_back("scripts/dead.gm");
	scripts.push_back("scripts/move.gm");
	scripts.push_back("scripts/idle.gm");

	std::string allScript = "";
	for (int i = 0; i < scripts.size(); i++)
	{
		std::ifstream file(scripts[i]);
		if (!file)
			return GM_EXCEPTION;
		allScript += std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
		file.close();
	}
	return a_machine.ExecuteString(allScript.c_str());
}

void handleErrors(gmMachine &a_machine)
{
	gmLog &log = a_machine.GetLog();
	// Get the first error
	bool firstError = true;
	const char *err = log.GetEntry(firstError);
	while (err)
	{
		std::cout << "Compilation error: -" << err << std::endl;
		err = log.GetEntry(firstError);
	}
}

void CFSM::SetUnit(CUnits * unit)
{
	gmCall  call;
	float posx, posy;
	if (call.BeginGlobalFunction(&gm, "set_m_positionx"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			posx = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_positiony"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			posy = myReturn;
		}
	}
	unit->SetPosition(CVector2D(posx, posy));
	if (call.BeginGlobalFunction(&gm, "set_m_speed"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_speed = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_v2Directionx"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_v2Direction.x = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_v2Directiony"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_v2Direction.y = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_fHp"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_fHp = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_bSelectable"))
	{
		call.End();
		int myReturn = 0;
		if (call.GetReturnedInt(myReturn)) {
			unit->m_bSelectable = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_fReloadTime"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_fReloadTime = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_fRotingTimer"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_fRotingTimer = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_fConstructionTimer"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_fConstructionTimer = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_v2Coordinatesx"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_v2Coordinates.x = myReturn;
		}
	}
	if (call.BeginGlobalFunction(&gm, "set_m_v2Coordinatesy"))
	{
		call.End();
		float myReturn = 0;
		if (call.GetReturnedFloat(myReturn)) {
			unit->m_v2Coordinates.y = myReturn;
		}
	}

}

void CFSM::Init()
{
	static gmFunctionEntry lib[] =
	{
		{ "MUL", gm_myMultiply }
	};
	gm.RegisterLibrary(lib, sizeof(lib) / sizeof(lib[0]));
	int ret = gmLoadAndExecuteScript(gm);
	if (ret != 0)
	{
		// There were errors in the script, exit gracefully
		handleErrors(gm);
		return;
	}

	gmCall  call;
	if (call.BeginGlobalFunction(&gm, "setStates"))
	{
		call.AddParamInt(STATEIDLE);
		call.AddParamInt(STATEMOVETO);
		call.AddParamInt(STATEATTACK);
		call.AddParamInt(STATEDEAD);
		call.AddParamInt(STATERECOLLECT);
		call.AddParamInt(STATEROTING);
		call.AddParamInt(STATEBUILD);
		call.AddParamInt(STATEGARRISON);
		call.End();
	}
	for (auto state = m_States.begin(); state != m_States.end(); state++)
	{
		(*state)->gm = &gm;
	}
	CUnits one;
	one.m_State = STATEIDLE;
	one.m_Manager = &manager;
	one.m_bSelectable = 1;
	one.SetPosition(CVector2D(0, 0));
	m_pUnits.push_back(one);
	m_pUnits.back().allUnits = &m_pUnits;
}

void CFSM::SetState(CUnits *unit, int state)
{
	m_States[unit->m_State]->OnExit(unit);
	unit->m_State = state;
	m_States[unit->m_State]->OnEnter(unit);
}

void CFSM::Update(float deltaTime)
{
	for (auto &unit : m_pUnits) {
		gmCall  call;
		if (call.BeginGlobalFunction(&gm, "set_unit"))
		{
			call.AddParamFloat(unit.m_speed);
			call.AddParamFloat(unit.m_v2Direction.x);
			call.AddParamFloat(unit.m_v2Direction.y);
			call.AddParamFloat(unit.m_fHp);
			call.AddParamInt(unit.m_bSelectable);
			call.AddParamFloat(unit.m_fReloadTime);
			call.AddParamFloat(unit.m_fRotingTimer);
			call.AddParamFloat(unit.m_fConstructionTimer);
			call.AddParamFloat(unit.m_v2Coordinates.x);
			call.AddParamFloat(unit.m_v2Coordinates.y);
			call.AddParamFloat(unit.GetPosition().x);
			call.AddParamFloat(unit.GetPosition().y);
			call.End();
		}
		int oldState = unit.m_State;
		int idState = m_States[unit.m_State]->Update(&unit, deltaTime);
		if (idState != oldState)
		{
			SetState(&unit, idState);
		};
		SetUnit(&unit);
	}
}

CFSM::CFSM()
{
	m_States.resize(COUNTSTATES);
	m_States[STATEIDLE] = new CIdle();
	m_States[STATEMOVETO] = new CMoveTo();
	m_States[STATEATTACK] = new CAttack();
	m_States[STATEDEAD] = new CDead();
	m_States[STATEROTING] = new CRoting();
	m_States[STATERECOLLECT] = new CRecollect();
	m_States[STATEBUILD] = new CBuild();
	m_States[STATEGARRISON] = new CGarrison();
}


CFSM::~CFSM()
{
}
