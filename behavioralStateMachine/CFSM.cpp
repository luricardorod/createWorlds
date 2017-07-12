#include "CFSM.h"
#include "CIdle.h";
#include "CMoveTo.h";
#include "CAttack.h";
#include "CDead.h";
#include "CRoting.h";
#include "CRecollect.h";
#include "CBuild.h";
#include "CGarrison.h";

void CFSM::SetState(CUnits *unit, int state)
{
	m_States[unit->m_State]->OnExit(unit);
	unit->m_State = state;
	m_States[unit->m_State]->OnEnter(unit);

}

void CFSM::Update(float deltaTime)
{
	for (auto &unit : m_pUnits) {
		int idState = m_States[unit->m_State]->Update(unit, deltaTime);
		if (idState != COUNTSTATES)
		{
			SetState(unit.get(), idState);
		};
	}
}

CFSM::CFSM()
{
	m_States = new CStates*[COUNTSTATES];
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
