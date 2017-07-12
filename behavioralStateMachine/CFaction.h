#pragma once
#include <vector>
#include <memory>


class CFaction
{
public:
	int m_iID;
	int	m_iMaxPopulation;
	std::vector<std::shared_ptr<int>> m_viDiplomacy;
	std::vector<std::shared_ptr<int>> m_viGroup;
	int	m_iResource;
	//Modifiers
	CFaction();
	~CFaction();

};

