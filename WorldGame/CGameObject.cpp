#include "CGameObject.h"

CGameObject::~CGameObject()
{
}

void CGameObject::SetPosition(CVector2D position)
{
	m_CVec2Position = position;
}

CVector2D CGameObject::GetPosition()
{
	return m_CVec2Position;
}

CGameObject::CGameObject()
{
}
