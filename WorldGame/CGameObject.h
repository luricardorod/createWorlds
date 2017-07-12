#pragma once
#include "CVector2D.h"
enum ClassEnum
{
	CLASSBOID,
	CLASSOBSTACLE,
	CLASSUNIT
};

class CGameObject
{
protected:
	CVector2D m_CVec2Position;
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual unsigned short GetClassId() = 0;
	virtual ~CGameObject();
	CGameObject();
	CVector2D GetPosition();
	void SetPosition(CVector2D position);
};

