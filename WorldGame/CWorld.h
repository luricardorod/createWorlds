#pragma once

#include "CGameObject.h"
#include <vector>
#include <memory>

class CWorld
{
public:
	std::vector<std::shared_ptr<CGameObject>> m_pGameObjects;

	void Init();
	void Destroy();
	void Update(float delta);
	void Render();

	CWorld();
	~CWorld();
};