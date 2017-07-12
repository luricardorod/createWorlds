#pragma once
#include <memory>
#include <vector>
#include "CVector2D.h"
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
	CVector2D m_v2Direction;
	float m_fHp;
	int m_State;
	int m_iGroupId;
	bool m_bSelectable;
	std::vector<std::shared_ptr<CUnits>>* m_vQueueConstruction;
	std::vector<std::shared_ptr<CUnits>>* m_vListaGarrison;
	float m_fReloadTime;
	float m_fRotingTimer;
	float m_fConstructionTimer;
	CUnits *m_UnitInteract;
	CWorld *m_World;
	CManager *m_Manager;
	CVector2D m_v2Coordinates;
	bool EnemyInVisionRange();
	bool IsAnEnemyFaction(int id);
	bool IsBelic();
	bool CanEnter(CUnits* unit);
	CUnits();
	~CUnits();
};
	
