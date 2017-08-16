#pragma once
#include <memory>
#include <vector>
#include "CGameObject.h"
#include "CWorld.h"
#include "CManager.h"
class CUnits:public CGameObject
{
public:
	void Init(int idType);
	void Destroy();
	void Update(float delta);
	void Render();
	unsigned short GetClassId();
	int m_iId;
	int m_iIdType;
	int m_iIdFaction;
	int m_State;
	int m_iGroupId;
	std::vector<CUnits*>* m_vQueueConstruction;
	std::vector<CUnits*>* m_vListaGarrison;
	std::vector<CUnits>* allUnits;
	CUnits *m_UnitInteract;
	CWorld *m_World;
	CManager *m_Manager;

	float m_speed;
	CVector2D m_v2Direction;
	float m_fHp;
	int m_bSelectable;
	float m_fReloadTime;
	float m_fRotingTimer;
	float m_fConstructionTimer;
	CVector2D m_v2Coordinates;
	bool EnemyInVisionRange();
	bool IsAnEnemyFaction(int id);
	bool IsBelic();
	bool CanEnter(CUnits* unit);
	CUnits();
	~CUnits();
};
	
