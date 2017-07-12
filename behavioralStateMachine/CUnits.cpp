#include "CUnits.h"
#include "definitions.h"
#include "CWorld.h"
void CUnits::Init(int idType)
{
	m_UnitInteract = NULL;
}

void CUnits::Destroy()
{
	this->~CUnits();
}

void CUnits::Update(float delta)
{
}

void CUnits::Render()
{
}

unsigned short CUnits::GetClassId()
{
	return CLASSUNIT;
}

bool CUnits::EnemyInVisionRange()
{
	for (auto &gameObject : m_World->m_pGameObjects) {
		if (gameObject->GetClassId() == CLASSUNIT)
		{
			CUnits* tempUnit = std::dynamic_pointer_cast<CUnits>(gameObject).get();
			if (IsAnEnemyFaction(tempUnit->m_iIdFaction))
			{
				float distance = (tempUnit->GetPosition() - GetPosition()).Magnitude();
				if (distance < m_Manager->GetType(m_iIdType)->m_fVisionRange)
				{
					m_UnitInteract = tempUnit;
					return true;
				}
			}
		}
	}
	return false;
}

bool CUnits::IsAnEnemyFaction(int id)
{
	return m_Manager->GetType(m_iIdType)->m_bIsBelic;
}

bool CUnits::IsBelic()
{
	return false;
}

bool CUnits::CanEnter(CUnits* unit)
{
	return unit->m_Manager->GetType(unit->m_iIdType)->m_iMaxGarrison < unit->m_vListaGarrison->size();
}

CUnits::CUnits()
{
}


CUnits::~CUnits()
{
}
